# Объектно-ориентированное программирование

Для начала нужны переменные, функции, ссылки и указатели из [основ C++](../basics/README.md).
Уроки [«073. Класс и объект»](lesson-073-oop-class-object/README.md) — [«081. Указатель this»](lesson-081-oop-this-pointer/README.md) вводят классы, объекты, методы, доступ, конструкторы и деструкторы.
Уроки сохраняют нумерацию курса; [курс и самостоятельные дополнения](../docs/course-sources.md)
разделены.

Уроки [«082. Конструктор копирования»](lesson-082-oop-copy-constructor/README.md) — [«097. Композиция и агрегация»](lesson-097-oop-aggregation-composition/README.md) объясняют копирование, перегрузки, доступ, `static` и состав объектов.
Уроки [«098. Наследование»](lesson-098-oop-inheritance/README.md) — [«108. Явный вызов базовой виртуальной функции»](lesson-108-oop-call-base-virtual-method/README.md) переходят к наследованию и виртуальным операциям;
109–114 — к нескольким базам и ромбу.
Каждый README разбирает именно исходник, включая различия `main*.cpp`.

## На что обратить внимание

- Инициализация нового объекта и присваивание существующему вызывают разные функции.
- Передача по значению может копировать или срезать объект; ссылка не владеет им.
- Поля по значению связывают время жизни компонента с владельцем.
- `public`/`protected`/`private` регулируют доступ, `virtual` — динамический вызов.
- Порядок создания баз/полей задаётся определением класса, не списком в конструкторе.
- Полиморфному удалению через базовый указатель нужен корректный виртуальный деструктор.

В учебном `operator=` урока [«083. Копирующее присваивание»](lesson-083-oop-operator-overloading-assignment/README.md) есть ограничения самоприсваивания и исключений.
В 97 Cap по значению тоже является композицией. Комментарии 99 не везде
соответствуют фактическому `private`-наследованию. Эти нюансы разобраны
в локальных README; исходные варианты сохранены.
Продолжение владения ресурсами — [RAII](../basics/additions/09-raii/README.md),
[правило нуля, трёх и пяти](../basics/additions/11-rule-of-zero-five/README.md)
и [гарантии исключений](../exceptions/additions/04-exception-guarantees/README.md).

## Дополнения вне курса

[Дополнения по ООП](additions/README.md): декремент после урока [«086. Префиксный и постфиксный ++»](lesson-086-oop-operator-overloading-increment-decrement/README.md),
композиция и агрегация со ссылкой на внешний объект после урока [«097. Композиция и агрегация»](lesson-097-oop-aggregation-composition/README.md).
Новые самостоятельные примеры находятся в `oop/additions/`.

## Карта уроков

- [073. Класс и объект](lesson-073-oop-class-object/README.md).
- [074. Методы класса](lesson-074-oop-class-methods/README.md).
- [075. public, private и protected](lesson-075-oop-access-modifiers/README.md).
- [076. Геттеры и сеттеры](lesson-076-oop-getters-setters/README.md).
- [077. Инкапсуляция и закрытые методы](lesson-077-oop-encapsulation/README.md).
- [078. Конструктор](lesson-078-oop-constructor/README.md).
- [079. Перегрузка конструкторов](lesson-079-oop-constructor-overloading/README.md).
- [080. Деструктор и выход из блока](lesson-080-oop-destructor/README.md).
- [081. Указатель this](lesson-081-oop-this-pointer/README.md).

- [082. Конструктор копирования](lesson-082-oop-copy-constructor/README.md).
- [083. Копирующее присваивание](lesson-083-oop-operator-overloading-assignment/README.md).
- [084. Сравнение объектов: == и !=](lesson-084-oop-operator-overloading-equal-not-equal/README.md).
- [085. Сложение объектов](lesson-085-oop-operator-overloading-addition/README.md).
- [086. Префиксный и постфиксный ++](lesson-086-oop-operator-overloading-increment-decrement/README.md).
- [087. Индексирование и возвращаемая ссылка](lesson-087-oop-operator-overloading-index/README.md).
- [088. Дружественная свободная функция](lesson-088-oop-friend-class-and-function/README.md).
- [089. Определение метода вне класса](lesson-089-oop-method-definition-outside-class/README.md).
- [090. Дружественный метод другого класса](lesson-090-oop-friend-method-in-class/README.md).
- [091. Дружественный класс](lesson-091-oop-friend-classes/README.md).
- [092. Статическое поле класса](lesson-092-oop-static-class-members/README.md).
- [093. Статический генератор идентификаторов](lesson-093-oop-static-id-generator/README.md).
- [094. Статические методы](lesson-094-oop-static-methods/README.md).
- [095. Вложенный класс](lesson-095-oop-nested-%28inner%29-classes/README.md).
- [096. Массив объектов](lesson-096-oop-array-of-objects/README.md).
- [097. Композиция и агрегация](lesson-097-oop-aggregation-composition/README.md).
- [098. Наследование](lesson-098-oop-inheritance/README.md).
- [099. Доступ при наследовании](lesson-099-oop-inheritance-access-modifiers/README.md).
- [100. Порядок конструкторов в цепочке наследования](lesson-100-oop-inheritance-constructor-order/README.md).
- [101. Порядок деструкторов](lesson-101-oop-inheritance-destructor-order/README.md).
- [102. Выбор конструктора базового класса](lesson-102-oop-inheritance-base-constructor-call/README.md).
- [103. Виртуальные методы и override](lesson-103-oop-virtual-methods-virtual-override-keywords/README.md).
- [104. Абстрактный класс](lesson-104-oop-abstract-class-pure-virtual-function/README.md).
- [105. Виртуальный деструктор](lesson-105-oop-virtual-destructor/README.md).
- [106. Чисто виртуальный деструктор](lesson-106-oop-pure-virtual-destructor/README.md).
- [107. Делегирующие конструкторы](lesson-107-oop-delegating-constructors/README.md).
- [108. Явный вызов базовой виртуальной функции](lesson-108-oop-call-base-virtual-method/README.md).
- [109. Множественное наследование](lesson-109-oop-multiple-inheritance/README.md).
- [110. Порядок конструкторов нескольких баз](lesson-110-oop-multiple-inheritance-constructor-order/README.md).
- [111. Порядок деструкторов нескольких баз](lesson-111-oop-multiple-inheritance-destructor-order/README.md).
- [112. Одинаковые имена в базовых классах](lesson-112-oop-multiple-inheritance-ambiguous-methods/README.md).
- [113. Интерфейс через абстрактный класс](lesson-113-oop-interfaces/README.md).
- [114. Ромб и виртуальное наследование](lesson-114-oop-virtual-diamond-inheritance/README.md).

## Сборка и запуск

Откройте корень проекта или отдельную папку урока в VS Code и выберите
нужный `main*.cpp`. **F5** запускает с отладчиком, **Ctrl+F5** — без отладчика.
Все `main`-варианты самостоятельные;
их не объединяют в одну программу. Используется C++17.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh 'oop/lesson-082-oop-copy-constructor/main.cpp'
./build/oop/lesson-082-oop-copy-constructor/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh 'oop/lesson-082-oop-copy-constructor/main.cpp'
& './build/oop/lesson-082-oop-copy-constructor/main.exe'
~~~

Заменяйте путь на нужный исходник. Папки со скобками и имена с пробелами
передавайте в кавычках. [Компиляторы и GDB](../README.md#требования) ·
[Устройство сборки](../scripts/README.md) · [Все уроки](../LESSONS.md).

## Курс и источники

[Введение в ООП, урок 72 и плейлист](https://www.youtube.com/watch?v=rZcTaRU7AAw&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX).
[Версии C++](../docs/cpp-versions.md) · [Справочники](../docs/references.md).
