#!/usr/bin/env python3
"""Resumen reproducible de la exportación del historial de alarmas (sin dependencias externas)."""
import csv
import statistics
from collections import Counter
from pathlib import Path

RUTA = Path(__file__).resolve().parent / "historial_alarmas_2026-11-22.csv"

with RUTA.open("r", encoding="utf-8-sig", newline="") as archivo:
    filas = list(csv.DictReader(archivo))

cerradas = [r for r in filas if r["Estado"] == "Detenida"]
sin_cierre = [r for r in filas if r["Estado"] != "Detenida"]
segundos = [int(r["Tiempo hasta detener la alarma"].split()[0]) for r in cerradas]
por_modo = Counter(r["Modo"] for r in filas)
por_origen = Counter(r["Origen"] for r in cerradas)

print("Archivo:", RUTA.name)
print("Activaciones:", len(filas))
print("Con detención registrada:", len(cerradas))
print("Sin detención registrada:", len(sin_cierre))
print("Con detención registrada (%):", round(len(cerradas) * 100 / len(filas), 1) if filas else 0)
print("Por modo:")
for modo, cantidad in sorted(por_modo.items()):
    print("  ", modo + ":", cantidad)
print("Por origen de detención:")
for origen, cantidad in sorted(por_origen.items()):
    print("  ", origen + ":", cantidad)
if segundos:
    print("Tiempo medio hasta detención registrada (s):", round(statistics.mean(segundos), 2))
    print("Mediana (s):", statistics.median(segundos))
    print("Rango (s):", min(segundos), "a", max(segundos))
print("IDs sin cierre:", ", ".join(r["ID"] for r in sin_cierre) or "ninguno")
print("Nota: falta de cierre registrado NO demuestra una causa específica.")
