# Локальные проверки сетевых уроков

Соберите нужные `.cpp` по [инструкциям сетевого раздела](../README.md#локальная-проверка).
Команды ниже выполняются из корня репозитория. Службы слушают только `127.0.0.1`;
отправки в Интернет и LAN broadcast нет. Загрузка Python-пакетов требуется один
раз при установке, не во время тестов. Используйте Python 3.11 или новее.

## Зависимости Python

Базовому `smoke.py` и проверкам чата `smoke_chat.py` достаточно стандартной
библиотеки Python. `smoke_advanced.py` и полный `smoke_extended.py` дополнительно
используют [requirements.txt](requirements.txt): `amqtt` — настоящий брокер MQTT,
`h2` — локальный HTTP/2-сервер, `aioquic` — HTTP/3-сервер поверх QUIC/UDP.
Версии прямых зависимостей закреплены для воспроизводимости.

Linux:

```bash
python3 -m venv build/networking-checks-venv
build/networking-checks-venv/bin/python -m pip install -r bonus/networking/tests/requirements.txt
build/networking-checks-venv/bin/python -B bonus/networking/tests/smoke_advanced.py
build/networking-checks-venv/bin/python -B bonus/networking/tests/smoke_extended.py
```

На Debian/Ubuntu для создания окружения может потребоваться пакет `python3-venv`.
Windows, PowerShell; `C:/msys64/mingw64/bin` должен быть в `PATH` для DLL и OpenSSL:

```powershell
python -m venv build/networking-checks-venv
& .\build\networking-checks-venv\Scripts\python.exe -m pip install -r bonus/networking/tests/requirements.txt
& .\build\networking-checks-venv\Scripts\python.exe -B bonus/networking/tests/smoke_advanced.py
& .\build\networking-checks-venv\Scripts\python.exe -B bonus/networking/tests/smoke_extended.py
```

Полная проверка требует `libcurl` с HTTP/2 **и** HTTP/3. Если текущая сборка не
поддерживает их или пакеты Python не установлены, допустим только явный пропуск:
добавьте `--skip-services` к `smoke_advanced.py` или `smoke_extended.py`.
Он пропускает MQTT и успешные обмены HTTP/2–3, но оставляет WSS, `strand` и
доступные проверки возврата к HTTP/1.1. Строка `SKIP` не означает проверку
пропущенного протокола. Опциональный `--multicast` у расширенного набора
по-прежнему включает отдельную проверку multicast через loopback.

Тесты ждут `Listening`, `Subscribed` и ответы протоколов; произвольные задержки
не используются как признак готовности. Успех — строки `PASS` и код `0`;
ошибка вызывает исключение и ненулевой код. Все запущенные процессы убираются
при выходе. Сертификаты и передаваемые файлы создаются во временных каталогах
внутри `build/` и удаляются после проверки.

## Сертификат для ручных примеров

Сначала создайте каталог: `mkdir -p build/networking-tls` на Linux или
`New-Item -ItemType Directory -Force build/networking-tls` в PowerShell.
Затем одна и та же команда для обеих систем:

```text
openssl req -x509 -newkey rsa:2048 -nodes -days 1 -subj /CN=localhost -addext subjectAltName=DNS:localhost -keyout build/networking-tls/key.pem -out build/networking-tls/cert.pem
```

Ключ записывается без пароля для локального учебного сервера. Сертификат действителен
одни сутки и содержит имя `localhost`, без IP-адреса `127.0.0.1`.
Клиенту передаётся `cert.pem` как явно доверенный сертификат; `key.pem` остаётся
у сервера. После истечения срока создайте пару заново. Эти файлы генерируются,
в Git не добавляются. В MSYS2 Bash преобразование аргумента `/CN=localhost`
может мешать OpenSSL; на Windows запускайте команду из PowerShell.

## Службы для ручного запуска

[local_services.py](local_services.py) запускает ограниченные локальные службы:
`mqtt`, `h1`, `h2` или `h3`. Они конечны: по умолчанию 60 секунд, время задаётся
`--seconds`. Это вспомогательные службы для уроков, не полноценные HTTP-серверы.

Linux, брокер для [урока MQTT](../lesson-22-mqtt/README.md):

```bash
build/networking-checks-venv/bin/python -B bonus/networking/tests/local_services.py mqtt --port 1883 --seconds 120
```

Windows, тот же брокер:

```powershell
& .\build\networking-checks-venv\Scripts\python.exe -B bonus/networking/tests/local_services.py mqtt --port 1883 --seconds 120
```

Для HTTPS замените режим и добавьте файлы сертификата. Linux:

```bash
build/networking-checks-venv/bin/python -B bonus/networking/tests/local_services.py h2 --port 42023 --cert build/networking-tls/cert.pem --key build/networking-tls/key.pem
```

Windows:

```powershell
& .\build\networking-checks-venv\Scripts\python.exe -B bonus/networking/tests/local_services.py h2 --port 42023 --cert build/networking-tls/cert.pem --key build/networking-tls/key.pem
```

`h1` и `h2` слушают TCP; `h3` слушает UDP с тем же синтаксисом аргументов.
Чтобы проверить другой режим, дождитесь завершения службы или остановите её
Ctrl+C и запустите заново. `--port 0` выбирает свободный порт, который служба
печатает в `Listening`. При штатном истечении времени и Ctrl+C — код `0`,
при ошибке настройки или занятом порте — ненулевой код.

Источники API: [aMQTT Broker](https://amqtt.readthedocs.io/en/latest/references/broker/),
[hyper-h2](https://python-hyper.org/projects/h2/en/stable/),
[aioquic](https://aioquic.readthedocs.io/en/latest/asyncio.html).
