# Дополнительные направления

Авторские учебные материалы вне исходного курса SimpleCode.
Для самостоятельного направления создаётся отдельная папка с последовательностью
уроков, своим README и настройками запуска Windows/Linux.
В каждом авторском разделе папки нумеруются с `01` по порядку изучения;
исходный курс SimpleCode сохраняет собственные номера и порядок.

- [Рефлексия — reflection](reflection/README.md): 30 уроков от RTTI и traits до C++26 и практических применений; Windows/Linux.
- [Сети — networking](networking/README.md): сокеты, TCP, UDP, HTTP, HTTPS, Asio,
  WebSocket/WSS, многопоточный Asio, MQTT, HTTP/2–3 и итоговый чат
  с heartbeat и переподключением.
- [Базы данных — PostgreSQL](databases/postgresql/README.md): 20 уроков от
  подключения и CRUD до транзакций, индексов, блокировок и резервных копий.
- [Корутины и генераторы](coroutines/README.md): awaiter, результаты, время жизни, отмена, потоки,
  исключения и `std::generator`.
- [Контракты](contracts/README.md): предусловия, постусловия, режимы проверки, исключения и инварианты.
- [Execution](execution/README.md): senders/receivers, исходы операции и планировщик.
- [Модули](modules/README.md): интерфейс, разделы, header units, `import std` и пересоздание CMI.

Дополнения к существующему разделу многопоточности остаются в
[multithreading/additions](../multithreading/additions/README.md).
Дополнения к основам находятся в [basics/additions](../basics/additions/README.md),
к потокам и файлам — в [io/additions](../io/additions/README.md).
Глобальный additions предназначен для новых направлений, которых не было в курсе.

[Все уроки проекта](../LESSONS.md).
