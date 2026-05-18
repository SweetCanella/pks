# Elevator Simulator

Учебный консольный симулятор работы группы лифтов в многоэтажном здании.
Программа моделирует приём вызовов с этажей, распределение их между
лифтами по выбранной стратегии и сбор итоговой статистики обслуживания.

Это **промежуточная** (skeleton) версия проекта: реализованы все
ключевые классы из UML-диаграмм (`Simulation`, `Dispatcher`, `Elevator`,
`IDispatchStrategy`, `NearestElevatorStrategy`, `MinQueueStrategy`,
`StrategyFactory`, `Statistics`, `ThreadSafeQueue<T>`), которые
демонстрируют применение паттернов **Singleton, Strategy, Factory
Method, Producer-Consumer, Observer**.

## Структура проекта

```
KR3/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── dispatcher.h
│   ├── elevator.h
│   ├── i_dispatch_strategy.h
│   ├── i_request_completion_listener.h
│   ├── min_queue_strategy.h
│   ├── nearest_elevator_strategy.h
│   ├── request.h
│   ├── simulation.h
│   ├── statistics.h
│   ├── strategy_factory.h
│   └── thread_safe_queue.h
└── src/
    ├── dispatcher.cpp
    ├── elevator.cpp
    ├── main.cpp
    ├── min_queue_strategy.cpp
    ├── nearest_elevator_strategy.cpp
    ├── simulation.cpp
    ├── statistics.cpp
    └── strategy_factory.cpp
```

## Требования к сборке

- CMake **3.10+**
- Компилятор с поддержкой **C++17** (GCC 7+, Clang 5+, MSVC 19.14+).
- Поддержка стандартной библиотеки потоков (`std::thread`,
  `std::mutex`, `std::condition_variable`).

## Сборка (out-of-source)

```bash
cmake -S . -B build
cmake --build build
```

## Запуск

После сборки исполняемый файл лежит в каталоге `build/` (или
`build/Release/` при MSVC).

```bash
cd build
./elevator_sim                       # параметры по умолчанию
./elevator_sim 12 4 nearest          # 12 этажей, 4 лифта, стратегия "nearest"
./elevator_sim 20 5 min_queue        # стратегия по минимальной очереди
```

Поддерживаемые стратегии диспетчеризации:
- `nearest` — выбор ближайшего по этажу лифта (по умолчанию);
- `min_queue` — выбор лифта с минимальной очередью целей.

## Внешние библиотеки

- **Threads** (`find_package(Threads REQUIRED)`) — подключение
  системной библиотеки потоков (pthread на Linux/macOS, штатная
  реализация на Windows).

## Пример вывода

```
[Simulation] Starting elevator simulator
[Simulation] Config: floors=10, elevators=3, strategy=nearest
[Dispatcher] Registered 3 elevator(s)
[Dispatcher] Submitted request: floor=5 direction=up
[Dispatcher] Submitted request: floor=3 direction=down
[Dispatcher] Submitted request: floor=8 direction=up
[Dispatcher] Submitted request: floor=2 direction=down
[Elevator 1] Assigned target floor 5
[Elevator 1] Assigned target floor 3
[Elevator 1] Assigned target floor 2
[Elevator 1] Assigned target floor 8
[Elevator 1] Arrived at floor 5 (travelled 4 floor(s))
[Elevator 1] Arrived at floor 3 (travelled 2 floor(s))
[Elevator 1] Arrived at floor 2 (travelled 1 floor(s))
[Elevator 1] Arrived at floor 8 (travelled 6 floor(s))

[Statistics] Total processed: 4
[Statistics] Average wait: 0 ms
[Statistics] Maximum wait: 0 ms
[Statistics] Elevator 1 served 1 request(s)
[Statistics] Elevator 2 served 1 request(s)
[Statistics] Elevator 3 served 1 request(s)
[Simulation] Completed successfully
```
