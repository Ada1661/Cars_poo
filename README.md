# Car Management System

This small C++ program uses classes and inheritance to manage different types of cars (fuel-based, electric, and hybrid). You can add cars of each type, display them, compare their range (autonomy), and optimize the top speed of a selected model. This project was created for a simple OOP practice of the basics.

---

## Table of Contents

1. [Overview](#overview)  
2. [Project Structure](#project-structure)  
3. [Main Classes](#main-classes)  
4. [Features](#features)  

---

## Overview

When you run this program, a menu appears asking which type of car you want to add:
- **Fuel-based Car** (gasoline or diesel)  
- **Electric Car**  
- **Hybrid Car** (combines fuel and electric)

After adding one or more cars, the program will display all the cars you entered, find the model with the highest range, and let you increase the maximum speed of a chosen model (for example, by +10%).

---

## Project Structure

- `main.cpp`  
  - Contains all class definitions and the `main()` function that implements the interactive menu.

Everything is kept in a single file for simplicity. If you want to expand the project later, you could split it into headers (`.h`) and source files (`.cpp`).

---

## Main Classes

1. **`Masina`** (abstract base class)  
   - **Common attributes:**  
     - `an_productie` (int) – year of production  
     - `nume_model` (string) – model name  
     - `viteza_max` (int) – top speed in km/h  
     - `greutate` (float) – weight in kg  
   - **Virtual methods:**  
     - `virtual float autonomie() const = 0;` – compute the car’s range  
     - `virtual void citire();` – read shared attributes from input  
     - `virtual void afiseaza() const;` – display shared attributes

2. **`Masina_combustibil_fosil`** (inherits from `Masina`)  
   - **Additional attributes:**  
     - `tip_combustibil` (string) – type of fuel (gasoline/diesel)  
     - `capacitate_rezervor` (float) – tank capacity in liters  
   - **`autonomie()`** is calculated as:  
     ```cpp
     sqrt(greutate) * capacitate_rezervor
     ```
   - Overrides `citire()` and `afiseaza()` to include fuel details.

3. **`Masina_electrica`** (inherits from `Masina`)  
   - **Additional attribute:**  
     - `capacitate_baterie` (float) – battery capacity in kWh  
   - **`autonomie()`** is calculated as:  
     ```cpp
     capacitate_baterie * greutate * greutate
     ```
   - Overrides `citire()` and `afiseaza()` to include battery details.

4. **`Masina_hibrida`** (inherits from both `Masina_combustibil_fosil` and `Masina_electrica`)  
   - Combines attributes of both fuel-based and electric cars.  
   - **`autonomie()`** returns:  
     ```cpp
     autonomy_fuel + autonomy_electric
     ```
   - Overrides `citire()` and `afiseaza()` to include both fuel and battery fields.

5. **`Sistem_gestionare`**  
   - Stores all cars in a `std::vector<std::shared_ptr<Masina>>`.  
   - **Key functions:**  
     - `adauga_masina(...)` – add any object derived from `Masina`.  
     - `model_cu_autonomie_maxima()` – find and return the car with the highest range.  
     - `optimizeaza_viteza(...)` – increase the top speed of a chosen model by a percentage.  
     - `afiseaza_toate_masini()` – display details of all cars, using polymorphism so each subclass’s `afiseaza()` is called.

---

## Features

1. **Add Cars**  
   - Choose the car type (fuel-based, electric, or hybrid).  
   - The program asks step-by-step for the required information (year, model, top speed, weight, etc.). For hybrids, you also enter fuel type, tank capacity, and battery capacity.

2. **Display All Cars**  
   - When you select “Exit and display results,” the program lists all added cars.  
   - You’ll see both common details and type-specific data (fuel/battery) along with the calculated range.

3. **Find the Car with Maximum Range**  
   - After listing all cars, the program automatically determines which car has the highest range and displays it with its range value.

4. **Optimize Top Speed**  
   - You can enter a model name and the percentage by which you want to increase its top speed (e.g., +10%).  
   - If the model is found, the top speed is updated immediately, and a confirmation is printed.  
   - Then, the program shows the updated list of cars so you can see the new speed.
