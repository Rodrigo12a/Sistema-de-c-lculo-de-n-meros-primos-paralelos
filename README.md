# Sistema de cálculo de números primos paralelos

## 📌 Descripción

Este proyecto implementa un algoritmo para el cálculo de números primos utilizando cómputo paralelo con OpenMP, con el objetivo de mejorar el rendimiento frente a una solución secuencial.

---

## 🎯 Objetivos

- Implementar cálculo de números primos
- Aplicar paralelismo real
- Medir rendimiento
- Analizar speedup

---

## ⚙️ Tecnologías

- Lenguaje: C++
- Paralelismo: OpenMP
- Compilador: GCC

---

## 🧠 Algoritmo

Se utiliza la **Criba de Eratóstenes Segmentada**, la cual:

1. Calcula primos base hasta √M
2. Divide el rango en segmentos
3. Procesa cada segmento en paralelo

---

## Compilación

```bash
g++ -fopenmp -O3 src/main.cpp -o primes

---

## Compilación

Si no cuentas con el compilador `g++`, sigue estos pasos (Windows):

1. **Descargar MSYS2:** Ve a [msys2.org](https://www.msys2.org/) y descarga el instalador.
2. **Instalar el Toolchain:** Abre la terminal de MSYS2 y ejecuta:
   ```bash
   pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

Configurar el PATH: Agrega la carpeta de binarios (ej. C:\msys64\ucrt64\bin) a las Variables de Entorno de tu sistema.

Verificar: Abre una terminal y escribe g++ --version.

