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

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

ctest --test-dir build --output-on-failure
```

## Запуск приложения

```bash
./build/elevator_sim
./build/elevator_sim 5 2 min_queue
```

## Запуск тестов и сценариев

```bash
./build/unit_tests
./build/unit_tests "[elevator]"

./build/scenario_single_elevator
./build/scenario_nearest_dispatch
./build/scenario_min_queue_balance
./build/scenario_full_simulation
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
