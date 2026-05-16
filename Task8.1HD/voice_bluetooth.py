import asyncio
import speech_recognition as sr
from bleak import BleakScanner, BleakClient

DEVICE_NAME = "VoiceLightSystem"
CHAR_UUID = "19B10001-E8F2-537E-4F6C-D104768A1214"

recognizer = sr.Recognizer()

def listen():
    with sr.Microphone() as source:
        print("Say: bathroom, hallway, fan, or all off")
        recognizer.adjust_for_ambient_noise(source, duration=1)
        audio = recognizer.listen(source, timeout=8, phrase_time_limit=4)

    try:
        text = recognizer.recognize_google(audio).lower()
        print("You said:", text)

        if "bathroom" in text:
            return "bathroom"
        elif "hallway" in text:
            return "hallway"
        elif "fan" in text:
            return "fan"
        elif "off" in text:
            return "all off"
        else:
            print("Command not recognised")
            return None

    except Exception as e:
        print("Voice error:", e)
        return None

async def send(command):
    print("Searching for Arduino...")
    device = await BleakScanner.find_device_by_name(DEVICE_NAME)

    if device is None:
        print("Arduino not found")
        return

    async with BleakClient(device.address) as client:
        await client.write_gatt_char(CHAR_UUID, command.encode())
        print("Sent:", command)

async def main():
    while True:
        command = listen()
        if command:
            await send(command)

asyncio.run(main())
