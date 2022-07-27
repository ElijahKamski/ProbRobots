#include <random>
#include <iostream>

using namespace std;

enum Day {
    Sunny,
    Cloudy,
    Rainy
};

double getZeroOneRange(mt19937 &gen) {
    return (double) gen() / std::mt19937::max();
}

string dayToString(Day day) {
    if (day == Sunny) {
        return "Sunny";
    }
    if (day == Cloudy) {
        return "Cloudy";
    }
    return "Rainy";

}

Day sim(Day cur, mt19937 &gen) {
    double prob = getZeroOneRange(gen);
    if (cur == Sunny) {
        if (prob < .8) {
            return Sunny;
        }
        return Cloudy;
    }
    if (cur == Cloudy) {
        if (prob < .4) {
            return Sunny;
        }
        if (prob < .8) {
            return Cloudy;
        }
        return Rainy;
    }
    if (prob < 0.2) {
        return Sunny;
    }
    if (prob < 0.8) {
        return Cloudy;
    }
    return Rainy;
}

int main() {
    std::random_device rd;
    mt19937 gen(rd());
    long long s = 0, c = 0, r = 0;
    string start;
    long long n;
    Day cur = Sunny;
    cout << "Enter the today's weather: ";
    cin >> start;
    if (start == "cloudy") {
        cur = Cloudy;
    } else if (start == "rainy") {
        cur = Rainy;
    }
    cout << "Enter number of iterations: ";
    cin >> n;
    Day first = cur;
    for (long long i = 0; i < n; ++i) {
        //cout<<"DAY "<<i<<": "<< dayToString(cur)<<'\n';
        if (cur == Sunny) {
            s++;
        } else if (cur == Cloudy) {
            c++;
        } else {
            r++;
        }
        cur = sim(cur, gen);
    }
    cout << "Probabilities with first given weather: " << dayToString(first) << " and " << n << " iterations" << '\n';
    cout << "Probability of sunny day: " << (double) s / n << '\n';
    cout << "Probability of cloudy day: " << (double) c / n << '\n';
    cout << "Probability of rainy day: " << (double) r / n << '\n';
    return 0;
}