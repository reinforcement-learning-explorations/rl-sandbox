#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

void displayPathtoPrincess(int n, vector<string> grid)
{
    vector<vector<double>> V(n, vector<double>(n, 0.0));
    double convergence = numeric_limits<double>::max();
    double gamma = 1;
    double r = -1;
    double update = 0;
    while (convergence > 0)
    {
        convergence = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 'p')
                {
                    continue;
                }

                double V_prime = -numeric_limits<double>::max();
                if (i > 0)
                {
                    V_prime = V[i - 1][j];
                }
                if (i < n - 1)
                {
                    if (V_prime < V[i + 1][j])
                    {
                        V_prime = V[i + 1][j];
                    }
                }
                if (j > 0)
                {
                    if (V_prime < V[i][j - 1])
                    {
                        V_prime = V[i][j - 1];
                    };
                }
                if (j < n - 1)
                {
                    if (V_prime < V[i][j + 1])
                    {
                        V_prime = V[i][j + 1];
                    };
                }

                update = r + gamma * V_prime;
                convergence += abs(V[i][j] - update);
                V[i][j] = update;
            }
        }
    }

    int agent[] = {(n / 2), (n / 2)};
    while (true)
    {
        string move("UP");
        int move_steps[] = {-1, 0};
        double r = -numeric_limits<double>::max();

        int i = agent[0];
        int j = agent[1];
        if (i > 0)
        {
            r = V[i - 1][j];
        }
        if (i < n - 1)
        {
            if (r < V[i + 1][j])
            {
                r = V[i + 1][j];
                move = "DOWN";
                move_steps[0] = 1;
                move_steps[1] = 0;
            }
        }
        if (j > 0)
        {
            if (r < V[i][j - 1])
            {
                r = V[i][j - 1];
                move = "LEFT";
                move_steps[0] = 0;
                move_steps[1] = -1;
            }
        }
        if (j < n - 1)
        {
            if (r < V[i][j + 1])
            {
                r = V[i][j + 1];
                move = "RIGHT";
                move_steps[0] = 0;
                move_steps[1] = 1;
            }
        }

        cout << move << endl;
        agent[0] += move_steps[0];
        agent[1] += move_steps[1];
        if (grid[agent[0]][agent[1]] == 'p')
            break;
    }
}

int main(void) {
    vector<string> gridworld = {
        "p--",
        "-m-",
        "---"
    };
    displayPathtoPrincess(gridworld.size(), gridworld);
}