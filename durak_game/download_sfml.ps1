# Скрипт для скачивания и распаковки SFML для Windows
# Автоматически скачивает SFML 2.5.1 для MinGW GCC - 64-bit

# Создаем директорию для SFML
$sfmlDir = ".\external\SFML"
if (-not (Test-Path -Path $sfmlDir)) {
    New-Item -Path $sfmlDir -ItemType Directory -Force
}

# URL для скачивания SFML для MinGW GCC
$sfmlUrl = "https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip"
$sfmlZip = ".\external\sfml_mingw.zip"

# Скачиваем SFML
Write-Host "Скачивание SFML 2.5.1 для MinGW..."
Invoke-WebRequest -Uri $sfmlUrl -OutFile $sfmlZip

# Распаковываем архив
Write-Host "Распаковка SFML..."
Expand-Archive -Path $sfmlZip -DestinationPath ".\external" -Force

# Переименовываем распакованную директорию
$extractedDir = ".\external\SFML-2.5.1"
if (Test-Path -Path $extractedDir) {
    # Если целевая директория уже существует, удаляем её
    if (Test-Path -Path $sfmlDir) {
        Remove-Item -Path $sfmlDir -Recurse -Force
    }
    # Переименовываем распакованную директорию
    Rename-Item -Path $extractedDir -NewName "SFML"
}

# Удаляем временный архив
Remove-Item -Path $sfmlZip -Force

Write-Host "SFML успешно установлен в $sfmlDir"
Write-Host "Теперь вы можете собрать проект с помощью команды:"
Write-Host "mkdir build"
Write-Host "cd build"
Write-Host "cmake .. -G 'MinGW Makefiles' -DSFML_DIR=..\external\SFML\lib\cmake\SFML"
Write-Host "cmake --build ." 