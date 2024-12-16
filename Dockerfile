# Используем базовый образ с поддержкой wxWidgets и инструментов сборки
FROM debian:bullseye

# Устанавливаем необходимые зависимости
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libwxgtk3.0-gtk3-dev \
    libgtk-3-dev \
    && rm -rf /var/lib/apt/lists/*

# Копируем проект в контейнер
WORKDIR /app
COPY . .

# Собираем проект
RUN mkdir build && cd build && cmake .. && make

# Указываем команду для запуска приложения
CMD ["./build/StepwiseRegression"]
