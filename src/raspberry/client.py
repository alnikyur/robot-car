import serial
import sys
import tty
import termios
import time

# Функция для считывания одного символа без нажатия Enter
def get_char():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# Подключение к Arduino
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # Небольшая пауза для установления соединения

print("Управление серво и двигателем. Нажмите 'a' для поворота влево, 'd' для поворота вправо, 'w' для движения вперед, 's' для движения назад, 'q' для выхода.")

try:
    while True:
        char = get_char()  # Получаем нажатую клавишу

        if char == 'a':
            ser.write(b'a')  # Поворот влево
        elif char == 'd':
            ser.write(b'd')  # Поворот вправо
        elif char == 'w':
            ser.write(b'w')  # Вперед
        elif char == 's':
            ser.write(b's')  # Назад
        elif char == 'x':  # Отправляем стоп команду если клавиша отпущена
            ser.write(b'x')
        elif char == 'q':
            print("Завершение работы.")
            break  # Выход из цикла

finally:
    ser.close()  # Закрытие соединения
