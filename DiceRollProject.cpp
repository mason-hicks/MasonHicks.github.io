/**
 * DiceRoll.cpp
 * Mason Hicks
 * CMPSC 121H
 * 22 October 2018
 * Description: 5 hours + 2 Starbucks espresso doubleshots + 3 versions 
 *  = Runs a simulation of a specified number of dice
 **/
 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int roll(double *weights, int sides);
void validateSides(int &);
double validateWeights(double *weights, int sides);
int validateRolls();

int main(){
    int sides;
    double *weights;
    bool prereq[2] = {false, false};
    double totalWeight;
    srand(time(0));
    
    validateSides(sides);
    weights = new double[sides];
    for(int i=0; i<sides; i++){
        *(weights + i) = 1/(float)sides;
    }
    vector<int> counter(sides);
    
    int rolls = validateRolls();
    for(int i=0; i<rolls; i++){
        int r = roll(weights, sides);
        counter[r-1]++;
    }
    vector<double> chi(sides);
    double chiTotal = 0;
    for(int i=0; i<sides; i++){
        if(weights[i] != 0){
            chi[i] = (pow((counter[i]-weights[i]*rolls),2)/(weights[i]*rolls));
            chiTotal += chi[i];
        }
    }
    int chiLength = (int) log10(chiTotal);
    
    cout << "+-------------------+\n";
    cout << "| Rolls:" << setw(11) << rolls << " |\n";
    cout << "+--------+----------+----------+----------+---------+\n";
    cout << "|  Side  | Weight % | Observed | Expected |   X^2   |\n";
    cout << "+--------|----------+----------+----------+---------+\n";
    cout << setprecision(5) << fixed;
    for(int i=0; i<sides; i++){
        if(chi[i] != 0){
            cout << '|' << setw(7) << i+1 << " | " << setw(8) << setprecision(5) << fixed << weights[i] << " | " << setw(8) << counter[i] << " | " << setw(8) << (int) (weights[i]*rolls) << " | " << setw(7) << setprecision((int)(5-abs(log10(chi[i])))) << fixed << chi[i] << " |\n";
        } else {
            cout << '|' << setw(7) << i+1 << " | " << setw(8) << setprecision(5) << fixed << weights[i] << " | " << setw(8) << counter[i] << " | " << setw(8) << (int) (weights[i]*rolls) << " | " << setw(7) << setprecision(0) << fixed << chi[i] << " |\n";
        }
    }
    cout << "+--------|----------+----------+----------+---------+\n";
    cout << "|  Total |  1.00000 |" << setw(9) << rolls << " |" << setw(9) << rolls << " | " << setw(7) << setprecision(5-chiLength) << fixed << chiTotal << " |" << "\n";
    cout << "+--------|----------+----------+----------+---------+\n\n\n";
    for(int i=0; i<sides; i++){
        counter[i] = 0;
    }
    
    delete [] weights;
    weights = NULL;
    return 0;
}

int roll(double *weight, int sides){
    double chosenValue = rand() / (float)RAND_MAX;
    double top = 0;
    for(int i = 0; i < sides; i++){
        top += *(weight+i);
        if(chosenValue < top){
            return i+1;
        }
    }
}

void validateSides(int &sides){
    cout << "Enter the number of sides: ";
    cin >> sides;
    if(sides < 2){
        cout << "Invalid number of sides!\n";
        validateSides(sides);
    }
}

int validateRolls(){
    cout << "How many rolls would you like to simulate? ";
    int i;
    cin >> i;
    if(i < 0){
        cout << "Invalid number of rolls\n";
        return validateRolls();
    }
    return i;
}

double validateWeights(double *weights, int sides){
    int total = 0;
    for(int i=0; i<sides; i++){
        *(weights+i) = -1;
    }
    for(int i=0; i<sides; i++){
        while(*(weights+i) < 0){
            cout << "Enter weight for side " << i+1 << ": ";
            cin >> *(weights+i);
            if(*(weights+i) < 0){
                cout << "Invalid weight! Try again.\n";
            }
            total += *(weights+i);
        }
    }
    return total;
}

/** Sample output

Enter the number of sides: 2
How many rolls would you like to simulate? 10
+-------------------+
| Rolls:         10 |
+--------+----------+----------+----------+---------+
|  Side  | Weight % | Observed | Expected |   X^2   |
+--------|----------+----------+----------+---------+
|      1 |  0.50000 |        6 |        5 |  0.2000 |
|      2 |  0.50000 |        4 |        5 |  0.2000 |
+--------|----------+----------+----------+---------+
|  Total |  1.00000 |       10 |       10 | 0.40000 |
+--------|----------+----------+----------+---------+

**/