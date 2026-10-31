# Объектно-ориентированное программирование

Нужны классы, поля, функции, ссылки, new/delete. Уроки сохраняют нумерацию исходного курса;
пропуски номеров не означают потерю файлов.

Уроки 82–97 объясняют копирование, перегрузки, доступ, static и состав объектов.
Уроки 98–108 переходят к наследованию и виртуальным операциям;
109–114 — к нескольким базам и ромбу.
Каждый README разбирает именно исходник, включая различия main*.cpp.

## На что обратить внимание

- Инициализация нового объекта и присваивание существующему вызывают разные функции.
- Передача по значению может копировать или срезать объект; ссылка не владеет им.
- Поля по значению связывают время жизни компонента с владельцем.
- public/protected/private регулируют доступ, virtual — динамический вызов.
- Порядок создания баз/полей задаётся определением класса, не списком в конструкторе.
- Полиморфному удалению через базовый указатель нужен корректный виртуальный деструктор.

В учебном operator= урока 83 есть ограничения самоприсваивания и исключений.
В 97 Cap по значению тоже является композицией. Комментарии 99 не везде
соответствуют фактическому private-наследованию. Эти нюансы разобраны
в локальных README; исходные варианты сохранены.
Продолжение владения ресурсами — [RAII](../basics/bonus/02-raii/README.md),
[правило нуля/пяти](../basics/bonus/10-rule-of-zero-five/README.md)
и [гарантии исключений](../basics/bonus/15-exception-guarantees/README.md).

## Карта уроков

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

Откройте корень проекта или отдельную папку урока в VS Code,
выберите нужный main*.cpp и нажмите F5. Все main-варианты самостоятельные;
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
