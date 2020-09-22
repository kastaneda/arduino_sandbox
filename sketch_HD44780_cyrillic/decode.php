#!/usr/bin/env php
<?php

/*  А а Б б В в Г г Д д Е е Ё ё
    ￼Ж ж З з И и Й й К к Л л М м
    ￼Н н О о П п Р р С с Т т У у
    ￼Ф ф Х х Ц ц Ч ч Ш ш Щ щ Ъ ъ
    ￼Ы ы Ь ь Э э Ю ю Я я */

$cyrillicBaseROM = [
    'Б' => chr(160),
    'Г' => chr(161),
    'Ё' => chr(162),
    'Ж' => chr(163),
    'З' => chr(164),
    'И' => chr(165),
    'Й' => chr(166),
    'Л' => chr(167),
    'П' => chr(168),
    'У' => chr(169),
    'Ф' => chr(170),
    'Ч' => chr(171),
    'Ш' => chr(172),
    'Ъ' => chr(173),
    'Ы' => chr(174),
    'Э' => chr(175),
    'Ю' => chr(176),
    'Я' => chr(177),
    'б' => chr(178),
    'в' => chr(179),
    'г' => chr(180),
    'ё' => chr(181),
    'ж' => chr(182),
    'з' => chr(183),
    'и' => chr(184),
    'й' => chr(185),
    'к' => chr(186),
    'л' => chr(187),
    'м' => chr(188),
    'н' => chr(189),
    'п' => chr(190),
    'т' => chr(191),
    'ч' => chr(192),
    'ш' => chr(193),
    'ъ' => chr(194),
    'ы' => chr(195),
    'ь' => chr(196),
    'э' => chr(197),
    'ю' => chr(198),
    'я' => chr(199),
    'Д' => chr(224),
    'Ц' => chr(225),
    'Щ' => chr(226),
    'д' => chr(227),
    'ф' => chr(228),
    'ц' => chr(229),
    'щ' => chr(230),
];

$cyrillicASCII = [
    'А' => 'A',
    'а' => 'a',
    'В' => 'B',
    'Е' => 'E',
    'е' => 'e',
    'К' => 'K',
    'М' => 'M',
    'Н' => 'H',
    'О' => 'O',
    'о' => 'o',
    'Р' => 'P',
    'р' => 'p',
    'С' => 'C',
    'с' => 'c',
    'Т' => 'T',
    'у' => 'y',
    'Х' => 'X',
    'х' => 'x',
    'Ь' => 'b',
];

$cyrillicUkrainian = [
    'І' => 'I',
    'і' => 'i',
    'Ї' => chr(1),
    'ї' => chr(2),
    'Є' => chr(3),
    'є' => chr(4),
    'Ґ' => chr(5),
    'ґ' => chr(6),
];

$conv = $cyrillicBaseROM + $cyrillicASCII + $cyrillicUkrainian;

$data = file_get_contents("php://stdin");
$len = mb_strlen($data);

for ($i = 0; $i < $len; $i++) {
    $char = mb_substr($data, $i, 1);
    echo isset($conv[$char]) ? $conv[$char] : $char;
}
