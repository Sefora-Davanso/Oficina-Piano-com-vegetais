import serial
import keyboard
import time

# Altere conforme a porta serial do seu Arduino
porta = 'COM6'  # Ex: COM3 no Windows, /dev/ttyACM0 no Linux
baudrate = 9600

try:
    arduino = serial.Serial(porta, baudrate, timeout=1)
    time.sleep(2)  # Aguarda a conexão estabilizar
    print(f"Conectado ao Arduino na porta {porta}")
except:
    print(f"Erro ao conectar na porta {porta}")
    exit()

print("Aguardando toques... Pressione Ctrl+C para sair.")

try:
    while True:
        if arduino.in_waiting > 0:
            tecla = arduino.readline().decode('utf-8').strip()
            if tecla:
                print(f"Tecla recebida: {tecla}")
                keyboard.press_and_release(tecla)
except KeyboardInterrupt:
    print("\nEncerrando...")
    arduino.close()
