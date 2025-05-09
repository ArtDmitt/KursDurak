# Скрипт для генерации тестовых изображений карт
# Требует установленного ImageMagick (https://imagemagick.org/script/download.php)

# Проверяем, установлен ли ImageMagick
$imageMagickInstalled = $false
try {
    $imageMagickVersion = magick -version
    $imageMagickInstalled = $true
    Write-Host "ImageMagick найден: $imageMagickVersion"
} catch {
    Write-Host "ImageMagick не найден. Пожалуйста, установите ImageMagick с https://imagemagick.org/script/download.php"
    Write-Host "После установки добавьте путь к ImageMagick в переменную окружения PATH"
    exit 1
}

# Создаем директорию для карт
$cardsDir = ".\assets\cards"
if (-not (Test-Path -Path $cardsDir)) {
    New-Item -Path $cardsDir -ItemType Directory -Force
}

# Масти и ранги карт
$suits = @("hearts", "diamonds", "clubs", "spades")
$ranks = @("6", "7", "8", "9", "10", "jack", "queen", "king", "ace")

# Символы мастей
$suitSymbols = @{
    "hearts" = "♥";
    "diamonds" = "♦";
    "clubs" = "♣";
    "spades" = "♠"
}

# Цвета мастей
$suitColors = @{
    "hearts" = "red";
    "diamonds" = "red";
    "clubs" = "black";
    "spades" = "black"
}

# Создаем рубашку карты
$backFile = "$cardsDir\back.png"
Write-Host "Создание рубашки карты: $backFile"
magick -size 256x384 xc:navy -fill white -pointsize 40 -gravity center -draw "text 0,0 'ДУРАК'" $backFile

# Создаем карты для каждой масти и ранга
foreach ($suit in $suits) {
    $symbol = $suitSymbols[$suit]
    $color = $suitColors[$suit]
    
    foreach ($rank in $ranks) {
        $cardFile = "$cardsDir\${suit}_${rank}.png"
        Write-Host "Создание карты: $cardFile"
        
        # Создаем белую карту
        magick -size 256x384 xc:white -bordercolor black -border 2 `
            -fill $color -pointsize 60 -gravity center -draw "text 0,0 '$rank $symbol'" `
            -fill $color -pointsize 30 -gravity northwest -draw "text 10,10 '$rank'" `
            -fill $color -pointsize 30 -gravity northwest -draw "text 40,10 '$symbol'" `
            -fill $color -pointsize 30 -gravity southeast -draw "text -10,-10 '$rank'" `
            -fill $color -pointsize 30 -gravity southeast -draw "text -40,-10 '$symbol'" `
            $cardFile
    }
}

Write-Host "Генерация тестовых карт завершена. Создано $(($suits.Length * $ranks.Length) + 1) файлов в директории $cardsDir" 