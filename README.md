# 🚗 Vehicle Diagnostics & Anomaly Detection System

Acest proiect este un simulator complet (End-to-End) pentru monitorizarea stării unui vehicul în timp real. Sistemul generează date de la senzori, le analizează folosind Machine Learning pentru a detecta defecțiuni și le afișează într-un dashboard web interactiv.

##  Tehnologii Utilizate

* **C++ (Backend Simulator):** Generarea datelor folosind programare orientată pe obiecte (OOP) și distribuții statistice (Gauss) pentru un comportament realist al senzorilor.
* **Python & FastAPI:** Server REST API care preia datele, le validează cu Pydantic și servește interfața web.
* **Machine Learning (Scikit-Learn):** Utilizarea algoritmului *Isolation Forest* pentru detectarea automată a anomaliilor (defecțiuni senzori).
* **Frontend:** Dashboard live realizat cu HTML5, CSS3 și Chart.js pentru vizualizarea grafică a datelor.

##  Arhitectura Sistemului

1.  **Simulatorul (C++):** Patru senzori (RPM, Temperatură, Viteză, Presiune Ulei) generează valori. Există o șansă de 5% ca un senzor să raporteze o anomalie (defecțiune).
2.  **Stocarea:** Datele sunt salvate în format JSON Lines, permițând un flux continuu de informații.
3.  **Analiza (AI):** Backend-ul în Python analizează ultimele citiri și folosește un model de AI pentru a decide dacă valorile sunt normale sau reprezintă o eroare tehnică.
4.  **Vizualizarea:** Dashboard-ul web se actualizează la fiecare secundă, marcând cu roșu punctele unde sistemul a detectat probleme.

##  Cum se rulează proiectul

### 1. Pornirea Simulatorului (C++)
```bash
cd simulator
g++ -std=c++17 main.cpp sensors/*.cpp -o simulator_app
./simulator_app
```

### 2. Pornirea Backend-ului (Python)
```bash
cd backend
source venv/bin/activate
uvicorn main:app --reload
```
<img width="1351" height="757" alt="Screenshot 2026-03-31 at 18 46 00" src="https://github.com/user-attachments/assets/7a80c4e3-f82a-494e-ba0f-4cbff568a353" />

