#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {

    int n;
    int limit;

    printf("Enter number of appliances: ");
    scanf("%d", &n);

    char name[n][30];
    int power[n];
    int priority[n];
    int time[n];

    printf("\nEnter details of %d appliances:\n", n);

    for(int i = 0; i < n; i++) {
        printf("\nAppliance %d name: ", i+1);
        scanf("%s", name[i]);

        printf("Power consumption (W): ");
        scanf("%d", &power[i]);

        printf("Priority (1=low to 10=high): ");
        scanf("%d", &priority[i]);

        printf("Usage time (hours): ");
        scanf("%d", &time[i]);
    }

    printf("\nEnter maximum allowed power (W): ");
    scanf("%d", &limit);


    float cost_per_kwh = 8.0;


    int dp[n+1][limit+1];
    int ans = 0;


    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= limit; j++) {

            if(i == 0 || j == 0) {
                dp[i][j] = 0;
            }

            else if(power[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            }

            else {
                int in = priority[i-1] + dp[i-1][j - power[i-1]];
                int ex = dp[i-1][j];

                dp[i][j] = max(in, ex);
            }

            ans = dp[i][j];
        }
    }



    int w = limit;
    int total_power = 0;
    int total_hours = 0;

    printf("\n\n===== SMART ENERGY COST OPTIMIZATION RESULT =====\n");
    printf("Maximum Priority Achieved: %d\n\n", ans);
    printf("Selected appliances:\n");

    for(int i = n; i >= 1; i--) {
        if(dp[i][w] != dp[i-1][w]) {

            printf(" - %s (Power: %dW, Priority: %d, Time: %dh)\n",
                    name[i-1], power[i-1], priority[i-1], time[i-1]);

            total_power += power[i-1];
            total_hours += time[i-1];

            w -= power[i-1];
        }
    }


    float energy_kwh = (total_power * total_hours) / 1000.0;
    float total_cost = energy_kwh * cost_per_kwh;

    printf("\n----------------------------------------------\n");
    printf("Total Power Used: %d W\n", total_power);
    printf("Total Hours Used: %d h\n", total_hours);
    printf("Total Energy: %.2f kWh\n", energy_kwh);
    printf("Estimated Electricity Cost: Tk %.2f\n", total_cost);
    printf("----------------------------------------------\n");

    return 0;
}
