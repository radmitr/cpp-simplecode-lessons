# Стандартный API и внешние реализации

В проекте есть два явно выбираемых профиля. Переключение относится к сборке
примера и не заменяет системную библиотеку или содержимое `/opt/gcc`.

| Профиль | Команда сборки | Что проверяется |
|---|---|---|
| Стандартный | `bash scripts/build-linux.sh SOURCE.cpp` | API выбранной `libstdc++`; недоступное API возвращает `77` |
| Внешний | `REFERENCE_LIBRARIES=1 bash scripts/build-linux.sh SOURCE.cpp` | Закреплённая сторонняя реализация в `build/dependencies/reference` |

На Windows используйте MSYS2 Bash, `scripts/build-windows.sh` и бинарный файл `.exe`.
Для переменной окружения в PowerShell: `$env:REFERENCE_LIBRARIES = '1'`; после
проверки удалите её: `Remove-Item Env:REFERENCE_LIBRARIES`.

## Подготовка

Из корня проекта:

```bash
python3 scripts/prepare-reference-libraries.py
```

На первом запуске нужен Интернет; Python загружает архивы HTTPS, проверяет SHA-256
и отклоняет опасные пути/ссылки внутри архивов. На следующих запусках используется
подготовленная ревизия. Существующий каталог с другой ревизией не перезаписывается:
переместите его отдельно, затем повторите подготовку. Для проверки целостности
повторной распаковкой также переместите каталог библиотеки; сохранённый архив
снова сверяется с SHA-256. Маркер `.revision` означает выбранную ревизию, но не
является защитой от ручного редактирования уже распакованных заголовков.

Точные URL, коммиты и контрольные суммы находятся в
[reference-libraries.json](../../scripts/reference-libraries.json).
Исходники зависимостей и сборочные продукты игнорируются Git; в репозитории
хранятся только manifest, подготовка, учебные адаптеры и инструкции.
После подготовки `.ready` хранит SHA-256 manifest. При изменении manifest
сборка требует повторить подготовку и не использует молча прежние ревизии.
Системная установка, `sudo` и `/opt` не нужны.

| Библиотека | Закреплённый коммит | Отличие от стандартного профиля |
|---|---|---|
| NVIDIA stdexec | `4d0d52d9e716dd2d54f2f6400ad0f511d055ca48` | Пространство `stdexec`, а не `std::execution`; собственные расширения и `task` |
| Kokkos stdBLAS | `146f4743a953e51d7319156f50d932bca7a6507f` | `Kokkos::Experimental::linalg`, экспериментальный интерфейс P1673 |
| Kokkos mdspan | `a32a23b523953f9c4ce0efccd56b7563bf6d83db` | Представления `Kokkos::mdspan`, совместимые с выбранным stdBLAS |
| plf::hive | `cb5527fe43ff0d34aa69e4a7a069f0f49b1438c7` | Контейнер `plf::hive`, а не установленный `std::hive` |

Для stdBLAS генерируется конфигурация последовательного header-only выполнения:
внешние BLAS, TBB и runtime Kokkos не подключаются. `MDSPAN_USE_PAREN_OPERATOR=1`
включает доступ `A(i,j)`, который использует выбранный stdBLAS; современный доступ
через `[]` остаётся доступен. Заголовки зависимостей не исправляются вручную.
NVIDIA stdexec в этих уроках работает на CPU через `run_loop`; GPU SDK не нужен.

## Проверка

```bash
python3 scripts/check-additions.py --section additions/execution --profile reference --require-features
python3 scripts/check-additions.py --section stl/additions --profile reference --require-features
```

По умолчанию `check-additions.py` выбирает `--profile standard`, даже если ранее
в shell было `REFERENCE_LIBRARIES=1`. Отчёты сохраняются отдельно:
`build/additions-checks/standard/report.json` и `build/additions-checks/reference/report.json`.
Успех внешнего профиля подтверждает работу показанных алгоритмов на этих ревизиях;
он не превращает пропущенный стандартный API в проверенный.

Для IntelliSense внешнего профиля:

```bash
REFERENCE_LIBRARIES=1 bash scripts/generate-compile-commands.sh
```

Для возврата к обычному профилю повторите команду без переменной или с её значением `0`.
Расширение редактора может не понимать весь корутинный/модульный синтаксис даже
при правильных include paths; окончательный результат сборки проверяется GCC.

## Связанные темы

- [Каналы завершения](03-completion-channels/README.md).
- [Линейная алгебра](../../stl/additions/24-linalg/README.md).
- [Hive](../../stl/additions/25-hive/README.md).
- [stdexec](https://github.com/NVIDIA/stdexec).
- [stdBLAS](https://github.com/kokkos/stdBLAS).
- [plf::hive](https://github.com/mattreecebentley/plf_hive).
