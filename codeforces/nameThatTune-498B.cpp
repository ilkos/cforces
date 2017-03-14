#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Song {
  double guessProbability;
  int timeout;
};

struct GuessProb {
  GuessProb(Song song) : p(vector<double>(song.timeout + 1)) {
    double stateProbability = 1;
    for (int i = 1; i < song.timeout; ++i) {
      p[i] = song.guessProbability * stateProbability;
      stateProbability *= (1 - song.guessProbability);
    }
    p[song.timeout] = stateProbability;
  }
  
  vector<double> p;
};

class Solution {
 public:
  Solution(const vector<Song>& songs, const int totalTime) :
      totalTime(totalTime),
      memo(songs.size() + 1, vector<double>(totalTime + 1, -1)) {
    guessProbs.reserve(songs.size());
    for (auto song : songs) {
      guessProbs.push_back(GuessProb(song));
    }
  }
  
  double solve() {
    return calcRecursive(0, 0);
  }

 private:
  double calcRecursive(int currentSong, int currentTime) {
    if (currentSong >= guessProbs.size()) {
      return 0.0;
    }
    
    if (memo[currentSong][currentTime] >= 0) {
      return memo[currentSong][currentTime];
    }
    
    double result = 0.0;
    for (int i = 1; i < guessProbs[currentSong].p.size() && currentTime + i <= totalTime; ++i) {
      result += guessProbs[currentSong].p[i] * (1 + calcRecursive(currentSong + 1, currentTime + i));
    }
    return memo[currentSong][currentTime] = result;
  }

  const int totalTime;
  vector<GuessProb> guessProbs;
  vector<vector<double>> memo;
};

int main() {
  int n, T;
  cin >> n >> T;

  vector<Song> songs(n);
  for (int i = 0; i < n; ++i) {
    int intProbability;
    cin >> intProbability >> songs[i].timeout;
    songs[i].guessProbability = intProbability / 100.0;
  }
  
  Solution solution(songs, T);
  cout << setprecision(9) << fixed << solution.solve() << endl;
}
