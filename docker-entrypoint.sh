#!/bin/sh
set -e

cmd="${1:-app}"

print_help() {
    cat <<'EOF'
Использование: docker run elevator-sim [КОМАНДА] [АРГУМЕНТЫ]

Команды:
  app [floors] [elevators] [strategy]   запустить симулятор (по умолчанию)
                                        strategy: nearest | min_queue
  test | tests [аргументы Catch2]        запустить unit-тесты (Catch2)
  scenario <имя> [аргументы]             запустить тестовый сценарий
  scenarios | list                       показать список сценариев
  help                                   показать эту справку

Сценарии: single_elevator, nearest_dispatch, min_queue_balance, full_simulation
EOF
}

case "$cmd" in
    app)
        shift
        exec ./elevator_sim "$@"
        ;;
    test|tests)
        shift
        exec ./unit_tests "$@"
        ;;
    scenario)
        shift
        name="$1"
        if [ -z "$name" ]; then
            echo "Ошибка: не указано имя сценария." >&2
            print_help >&2
            exit 1
        fi
        shift
        bin="./scenario_${name}"
        if [ ! -x "$bin" ]; then
            echo "Ошибка: сценарий '${name}' не найден." >&2
            print_help >&2
            exit 1
        fi
        exec "$bin" "$@"
        ;;
    scenarios|list)
        echo "single_elevator nearest_dispatch min_queue_balance full_simulation"
        ;;
    help|-h|--help)
        print_help
        ;;
    *)
        exec ./elevator_sim "$@"
        ;;
esac
