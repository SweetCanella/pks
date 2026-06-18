FROM ubuntu:24.04 AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /project

COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel "$(nproc)"
RUN ctest --test-dir build --output-on-failure

FROM ubuntu:24.04 AS final

RUN apt-get update \
    && apt-get install -y --no-install-recommends libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /project/build/elevator_sim ./
COPY --from=builder /project/build/unit_tests ./
COPY --from=builder /project/build/scenario_single_elevator ./
COPY --from=builder /project/build/scenario_nearest_dispatch ./
COPY --from=builder /project/build/scenario_min_queue_balance ./
COPY --from=builder /project/build/scenario_full_simulation ./

COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN sed -i 's/\r$//' /usr/local/bin/docker-entrypoint.sh \
    && chmod +x /usr/local/bin/docker-entrypoint.sh

ENTRYPOINT ["docker-entrypoint.sh"]
CMD ["app"]
