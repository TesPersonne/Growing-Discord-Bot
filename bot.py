import discord
import serial
import asyncio

TOKEN = ""

CHANNEL_DATA_ID = 1379120424297959444  
CHANNEL_CTRL_ID = 1379120504253976627  

ser = serial.Serial('/dev/ttyUSB0', 115200)  

intents = discord.Intents.default()
intents.message_content = True

class MyClient(discord.Client):
    async def setup_hook(self):
        
        self.bg_task = asyncio.create_task(self.read_serial_and_send())

    async def on_ready(self):
        print(f"✅ Connecté en tant que {self.user}")

    async def on_message(self, message):
        if message.channel.id != CHANNEL_CTRL_ID or message.author == self.user:
            return

        cmd = message.content.strip().upper()
        if cmd in ["ARROSAGE_ON", "ARROSAGE_OFF", "BRUME_ON", "BRUME_OFF"]:
            ser.write((cmd + '\n').encode())
            await message.channel.send(f"✅ Commande `{cmd}` envoyée à l'ESP32.")
        else:
            await message.channel.send("❌ Commande inconnue. Utilise : ARROSAGE_ON, ARROSAGE_OFF, BRUME_ON, BRUME_OFF.")

    async def read_serial_and_send(self):
        await self.wait_until_ready()
        channel = self.get_channel(CHANNEL_DATA_ID)
        while not self.is_closed():
            if ser.in_waiting:
                line = ser.readline().decode().strip()
                if line.startswith("DATA;"):
                    try:
                        parts = line.split(";")
                        temp, hum, soil = parts[1], parts[2], parts[3]
                        msg = (
                            f"🌡️ Température : **{temp}°C**\n"
                            f"💧 Humidité air : **{hum}%**\n"
                            f"🌱 Humidité sol : **{soil}**"
                        )
                        await channel.send(msg)
                    except Exception as e:
                        print(f"Erreur parsing: {e} | ligne: {line}")
            await asyncio.sleep(1)

client = MyClient(intents=intents)
client.run(TOKEN)
