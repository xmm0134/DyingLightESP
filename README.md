# Dying Light – Internal Modding & Reverse Engineering Demo

**Disclaimer: This project is for educational and research purposes only.**

This project is an **internal runtime modification tool** for *Dying Light*, created to explore reverse engineering concepts, memory inspection, and dynamic patching within a game engine.  
It was developed purely as a **learning exercise** to understand how game data structures, rendering hooks, and player state systems operate internally.

---

## ⚠️ Important Notice

- **Educational Use Only**: Created to study reverse engineering, memory structures, and real-time game modification techniques.  
- **Single-Player Only**: Built and tested exclusively in single-player mode.  
- **Not for Online Use**: Not designed for or intended to alter multiplayer gameplay.  
- **Outdated Code**: Originally written two years ago and no longer maintained. Offsets and patterns will not work on current versions without updating.

---

## 📌 Overview

This tool demonstrates:

- Injecting into a game process  
- Locating and interacting with internal game structures  
- Implementing a custom overlay renderer  
- Modifying player and world parameters at runtime  
- Hooking engine functions for real-time visualization  

These techniques are commonly studied in systems programming, game engine internals, debugging, and modding communities.

---

## 🔧 Implemented Modules

- **Player State Patching**  
  - Health freeze  
  - Stamina adjustment  
  - Durability lock  

- **Inventory & Resource Tweaks**  
  - Ammo counter override  

- **Overlay Visualization**  
  - Dynamic object markers  
  - Skeleton and bounding-box representation  
  - Name labels for debugging purposes  

---

<img width="1920" height="1080" alt="Screenshot (79)" src="https://github.com/user-attachments/assets/9e3dc289-85bd-4752-899a-5cbaacb35f10" />

## Hotkeys
- INSERT: Show/Hide debug overlay
