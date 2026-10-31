# 02. Композиция и невладеющая связь

C++17. После [урока 97](../../lesson-097-oop-aggregation-composition/README.md).
Нужны поля класса, ссылки и области видимости. Это дополнительная модель вне курса.

В [main.cpp](main.cpp) используются два разных способа хранить шапку `Cap`:

- `Owner` содержит `Cap cap{"green"}` по значению. Это его собственный компонент:
  шапка создаётся и уничтожается вместе с владельцем.
- `Borrower` содержит `Cap& cap` — ссылку на внешний объект. Он использует
  шапку, но не управляет её уничтожением. Здесь это иллюстрирует агрегацию.

`external` создаётся до `Borrower` и живёт дольше него.
Присваивание `person.cap.color = "blue"` меняет внешнюю шапку.
После выхода из внутреннего блока `person` уничтожен, а `external` остаётся синим.
Собственная шапка `owner` всё это время остаётся зелёной.

~~~text
Borrowed cap: blue
External cap after borrower: blue
Owned cap: green
~~~

Ссылка не продлевает жизнь внешнего объекта. Если бы `external` был уничтожен
раньше последнего обращения через `Borrower`, ссылка стала бы висячей.
Указывать владение нужно по устройству полей и правилам времени жизни:
название предмета само по себе не делает связь агрегацией.
В исходном уроке оба поля `Brain` и `Cap` хранятся по значению.

## Сборка и запуск

Откройте `main.cpp`: **F5** — с отладчиком, **Ctrl+F5** — без отладчика.
Можно открыть корень проекта или папку этого бонуса.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh oop/bonus/02-composition-aggregation/main.cpp
./build/oop/bonus/02-composition-aggregation/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh oop/bonus/02-composition-aggregation/main.cpp
& .\build\oop\bonus\02-composition-aggregation\main.exe
~~~

Ввод не нужен. Программа возвращает `0` при верном результате,
`1` при нарушении встроенных проверок.
[Бонусы раздела](../README.md) · [Все уроки](../../../LESSONS.md).
