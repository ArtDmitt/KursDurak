# Скрипт для сборки проекта

# Проверяем, установлен ли SFML
$sfmlDir = ".\external\SFML"
if (-not (Test-Path -Path $sfmlDir)) {
    Write-Host "SFML не найден. Запускаем скрипт скачивания..."
    & .\download_sfml.ps1
}

# Создаем директорию для сборки
$buildDir = ".\build"
if (-not (Test-Path -Path $buildDir)) {
    New-Item -Path $buildDir -ItemType Directory -Force
}

# Переходим в директорию сборки
Set-Location -Path $buildDir

# Запускаем CMake для генерации проекта
Write-Host "Генерация проекта с помощью CMake..."
cmake .. -DSFML_DIR=..\external\SFML\lib\cmake\SFML

# Собираем проект
Write-Host "Сборка проекта..."
cmake --build . --config Release

# Возвращаемся в корневую директорию
Set-Location -Path ..

# Копируем DLL-файлы SFML в директорию с исполняемым файлом
Write-Host "Копирование DLL-файлов SFML..."
$dllSource = ".\external\SFML\bin"
$dllDest = ".\build\bin\Release"

if (-not (Test-Path -Path $dllDest)) {
    New-Item -Path $dllDest -ItemType Directory -Force
}

Copy-Item -Path "$dllSource\*.dll" -Destination $dllDest -Force

Write-Host "Сборка завершена. Исполняемый файл находится в $dllDest\durak_game.exe" 