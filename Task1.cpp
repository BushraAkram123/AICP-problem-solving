#include <iostream>
#include <string>
using namespace std;

// Constants for price and max stay hours
const double priceMorning[] = {2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 3.0};
const double priceEvening = 2.0;
const int maxStayMorning[] = {8, 2, 2, 2, 2, 2, 4};
const int maxStayEvening = 0;    // No parking allowed between midnight and 08:00

// Function to check the frequent parking number
bool checkFrequentParkingNumber(string frequentParkingNumber) 
{
    if (frequentParkingNumber.length() != 5) 
	{
        return false; // The number must consist of 4 digits and a check digit
    }

    int checkDigit = frequentParkingNumber[frequentParkingNumber.size() - 1] - '0';

    int sum = 0;

    for (int i = 0; i < 4; i++) 
	{
        if (!isdigit(frequentParkingNumber[i])) 
		{
            return false; // Check for non-digit characters
        }
        int digit = frequentParkingNumber[i] - '0';
        sum = sum + (digit * (4 - i));
    }

    int calculatedCheckDigit = (11 - (sum % 11)) % 11;

    return checkDigit == calculatedCheckDigit;
}

int main() 
{
    // Input variables
    string dayOfWeek;
    int arrivalHour;
    int hoursParked;
    string frequentParkingNumber;
    double totalCost = 0.0;

    // Get user input
    cout << "Enter the day of the week (Sunday to Saturday): ";
    cin >> dayOfWeek;
    cout << "Enter the hours of arrival (excluding minutes): ";
    cin >> arrivalHour;
    cout << "Enter the number of hours to leave your car: ";
    cin >> hoursParked;

    // Check if the user is eligible for a discount
    cout << "Enter your frequent parking number (if available): ";
    cin >> frequentParkingNumber;

    // Determine the price per hour based on the arrival time and day of the week
    int index = dayOfWeek == "Sunday" ? 0 : (dayOfWeek == "Monday" ? 1 : (dayOfWeek == "Tuesday" ? 2 : (dayOfWeek == "Wednesday" ? 3 : (dayOfWeek == "Thursday" ? 4 : (dayOfWeek == "Friday" ? 5 : 6)))));
    double pricePerHour;
    int maxStay;
    double discount = 0.0;

    if (arrivalHour >= 8 && arrivalHour <= 15) 
	{
        pricePerHour = priceMorning[index];
        maxStay = maxStayMorning[index];
        discount = 0.1; // 10% discount for morning arrivals
    } 
	else if (arrivalHour >= 16 && arrivalHour <= 23) 
	{
        pricePerHour = priceEvening;
        discount = 0.5; // 50% discount for evening arrivals
    } else 
	{
        cout << "Invalid arrival hour." << endl;
        return 1;
    }

    // Calculate the total cost
    if (hoursParked <= maxStay) 
	{
        totalCost = hoursParked * pricePerHour;
    } 
	else 
	{
        cout << "You've exceeded the maximum allowed parking duration." << endl;
        return 1;
    }

    // Apply a discount if the frequent parking number is correct
    if (!frequentParkingNumber.empty() && checkFrequentParkingNumber(frequentParkingNumber)) 
	{
        totalCost = totalCost * (1 - discount); // Apply the discount
    }

    // Display the total cost to the user
    cout << "Total cost: $" << totalCost << endl;

    return 0;
}

