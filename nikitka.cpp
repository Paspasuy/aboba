#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
 
const int MaxPlayerShipMovesPerStep = 1000;
const int StartShipsCount = 100;
const int MaxShipGroupsInSpace = 1000;
const int ShipsToCapturePlanet = 100;
const vector <int> ShipsToUpgradePlanet = { 100, 100, 200 };
const vector <int> PerLevelPlanetArmor = { 0, 100, 200, 300 };
 
int PlayerId, PlayerCount, PlanetCount;
vector <vector <int>> dist;
int NumberOfLastMoves;
 
vector <int> planet_PlayerId;
vector <int> planet_ShipCount;
vector <int> planet_Level;
vector <int> planet_Armor;
vector <int> myPlanets;
 
int flor = 7;
int max_level = 0;
 
int from_my_to_planet(int i) {
    int ans = 0;
    for (auto j : myPlanets) {
        ans = ans + dist[j][i];
    }
    return ans;
}
 
int compare(int i, int j) {
    if (i == 0) return j;
    if (j == 0) return i;
    if (from_my_to_planet(i) < from_my_to_planet(j)) return i;
    else return j;
}
 
signed main() {
    srand(time(NULL));
    // Кофнигурация
    cin >> PlayerId >> PlayerCount >> PlanetCount;
    dist.assign(PlanetCount + 1, vector <int>(PlanetCount + 1));
    for (int i = 1; i <= PlanetCount; i++) {
        for (int j = 1; j <= PlanetCount; j++) {
            cin >> dist[i][j];
        }
    }
 
    planet_PlayerId.assign(PlanetCount + 1, 0);
    planet_ShipCount.assign(PlanetCount + 1, 0);
    planet_Level.assign(PlanetCount + 1, 0);
    planet_Armor.assign(PlanetCount + 1, 0);
 
    while (true) { // игровой цикл
        // Последние ходы
        cin >> NumberOfLastMoves;
        if (NumberOfLastMoves == -1) return 0;
        for (int i = 0; i < NumberOfLastMoves; i++) {
            int send_PlayerId, send_FromPlanetId, send_ToPlanetId, send_Count;
            cin >> send_PlayerId >> send_FromPlanetId >> send_ToPlanetId >> send_Count;
        }
 
        // Мои ходы
        vector <pair <pair <int, int>, int>> moves;
 
        // Информация о планетах
        myPlanets.clear();
        for (int i = 1; i <= PlanetCount; i++) {
            cin >> planet_PlayerId[i] >> planet_ShipCount[i] >> planet_Level[i] >> planet_Armor[i];
            if (planet_PlayerId[i] == PlayerId && planet_Level[i] >= 1)
                myPlanets.push_back(i);
        }
 
        if (myPlanets.size() < max_level + 6) {
            int best = 0;
            for (int i = 1; i <= PlanetCount; i++) {
                if (planet_PlayerId[i] == PlayerId) {
                    if (planet_Level[i] < 1) {
                        if (planet_ShipCount[i] >= ShipsToCapturePlanet)
                            moves.push_back({ {i, i}, ShipsToCapturePlanet });
                        else
                            best = compare(best, i);
                    }
                }
                else
                    best = compare(best, i);
            }
            if (best > 0) {
                for (auto u : myPlanets) {
                    moves.push_back({ {u, best}, planet_ShipCount[u] });
                }
            }
        }
        else {
            for (auto u : myPlanets) {
                if (planet_Level[u] < 3 && planet_ShipCount[u] >= ShipsToUpgradePlanet[planet_Level[u]]) {
                    moves.push_back({ {u, u}, ShipsToUpgradePlanet[planet_Level[u]] });
                    if (planet_Level[u] == 2)
                        max_level++;
                }
            }
        }
 
        cout << moves.size() << endl;
        for (auto& move : moves) {
            cout << move.first.first << ' ' << move.first.second << ' ' << move.second << endl;
        }
    }
 
    return 0;
}
 
