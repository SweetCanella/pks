# Симулятор работы лифтов

Единый учебный проект по дисциплине «Программирование корпоративных систем».
Проект содержит консольное приложение, unit-тесты Catch2, демонстрационные сценарии и Docker-сборку.

## Структура

```text
include/              заголовочные файлы симулятора
src/                  исходный код приложения
tests/                unit-тесты, сценарии и Catch2
tests/scenarios/      демонстрационные сценарии
tests/third_party/    сторонние header-only зависимости
CMakeLists.txt        единая CMake-сборка
Dockerfile            многостадийная Docker-сборка
docker-entrypoint.sh  запуск app/test/scenario внутри контейнера
docker-compose.yml    удобные docker compose команды
```

## Локальная сборка

Команды рассчитаны на Windows и сборку через генератор Visual Studio:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release

ctest --test-dir build -C Release --output-on-failure
```

## Запуск приложения

```powershell
.\build\Release\elevator_sim.exe
.\build\Release\elevator_sim.exe 5 2 min_queue
```

## Запуск тестов и сценариев

```powershell
.\build\Release\unit_tests.exe
.\build\Release\unit_tests.exe "[elevator]"

.\build\Release\scenario_single_elevator.exe
.\build\Release\scenario_nearest_dispatch.exe
.\build\Release\scenario_min_queue_balance.exe
.\build\Release\scenario_full_simulation.exe
```

## Docker

```bash
docker build -t elevator-sim .

docker run --rm elevator-sim
docker run --rm elevator-sim app 5 2 min_queue
docker run --rm elevator-sim test
docker run --rm elevator-sim scenarios
docker run --rm elevator-sim scenario full_simulation
```

## Docker Compose

```bash
docker compose build
docker compose run --rm app
docker compose run --rm tests
```
