#!/usr/bin/env python3
"""Reconstruye exactamente el firmware 4.1 con registro sin alterar el original."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
PATCH = json.loads((HERE / "cambios_historial.json").read_text(encoding="utf-8"))
BASE = ROOT / PATCH["base"]
TARGET = HERE / "prototipo_4_1_revisiones.ino"

base_bytes = BASE.read_bytes()
blob_id = hashlib.sha1(b"blob " + str(len(base_bytes)).encode() + b"\x00" + base_bytes).hexdigest()
if blob_id != PATCH["base_blob_sha"]:
    raise SystemExit("La version base cambio: se cancela la generacion para evitar un .ino incorrecto.")

lineas = base_bytes.decode("utf-8").split("\n")
for cambio in reversed(PATCH["edits"]):
    i = cambio["start"]
    lineas[i:i + cambio["delete"]] = cambio["insert"]

resultado = "\n".join(lineas).encode("utf-8")
checksum = hashlib.sha256(resultado).hexdigest()
if checksum != PATCH["target_sha256"]:
    raise SystemExit("La verificacion SHA-256 fallo: no se escribio ningun archivo.")

TARGET.write_bytes(resultado)
print("Archivo creado y verificado:", TARGET)
print("SHA-256:", checksum)
