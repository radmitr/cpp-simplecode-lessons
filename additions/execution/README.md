# Execution: senders и планировщики

Нужны лямбды, RAII, многопоточность и корутины. Сначала разберите описание работы, connect/start и каналы завершения, затем композицию, планировщики и мост к корутинам. Для установленной libstdc++ основной API пока недоступен; работающий [внешний профиль](reference-libraries.md) использует закреплённый NVIDIA stdexec.

## Уроки

- [01. Описание работы через senders и receivers](01-senders/README.md) — `c++26`.
- [02. connect, start и собственный receiver](02-operation-state/README.md) — `c++26`.
- [03. Значение, ошибка и остановка](03-completion-channels/README.md) — `c++26`.
- [04. Объединение операций и зависимые шаги](04-composition/README.md) — `c++26`.
- [05. Планировщик и время жизни операции](05-schedulers/README.md) — `c++26`.
- [06. Переключение планировщика](06-scheduler-transfer/README.md) — `c++26`.
- [07. Senders внутри корутины](07-coroutine-interop/README.md) — `c++26`.

[Учебный маршрут](../../docs/learning-path.md) · [Версии и покрытие](../../docs/cpp-coverage.md).
