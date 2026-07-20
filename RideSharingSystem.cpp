#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Base class representing a general ride
class Ride {
private:
    string rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(
        const string& id,
        const string& pickup,
        const string& dropoff,
        double rideDistance
    )
        : rideID(id),
          pickupLocation(pickup),
          dropoffLocation(dropoff),
          distance(rideDistance) {}

    virtual ~Ride() = default;

    string getRideID() const {
        return rideID;
    }

    string getPickupLocation() const {
        return pickupLocation;
    }

    string getDropoffLocation() const {
        return dropoffLocation;
    }

    double getDistance() const {
        return distance;
    }

    // Virtual method overridden by each ride subclass
    virtual double calculateFare() const = 0;

    // Virtual method used to display ride information
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << endl;
        cout << "Pickup Location: " << pickupLocation << endl;
        cout << "Drop-off Location: " << dropoffLocation << endl;
        cout << "Distance: " << distance << " miles" << endl;
        cout << fixed << setprecision(2);
        cout << "Fare: $" << calculateFare() << endl;
    }
};

// Standard ride subclass
class StandardRide : public Ride {
private:
    static constexpr double RATE_PER_MILE = 2.00;

public:
    StandardRide(
        const string& id,
        const string& pickup,
        const string& dropoff,
        double distance
    )
        : Ride(id, pickup, dropoff, distance) {}

    double calculateFare() const override {
        return getDistance() * RATE_PER_MILE;
    }

    void rideDetails() const override {
        cout << "\n--- Standard Ride ---" << endl;
        Ride::rideDetails();
    }
};

// Premium ride subclass
class PremiumRide : public Ride {
private:
    static constexpr double RATE_PER_MILE = 3.50;

public:
    PremiumRide(
        const string& id,
        const string& pickup,
        const string& dropoff,
        double distance
    )
        : Ride(id, pickup, dropoff, distance) {}

    double calculateFare() const override {
        return getDistance() * RATE_PER_MILE;
    }

    void rideDetails() const override {
        cout << "\n--- Premium Ride ---" << endl;
        Ride::rideDetails();
    }
};

// Driver class
class Driver {
private:
    string driverID;
    string name;
    double rating;

    // Encapsulation: assigned rides remain private
    vector<shared_ptr<Ride>> assignedRides;

public:
    Driver(
        const string& id,
        const string& driverName,
        double driverRating
    )
        : driverID(id),
          name(driverName),
          rating(driverRating) {}

    void addRide(const shared_ptr<Ride>& ride) {
        if (ride == nullptr) {
            cout << "Cannot assign an invalid ride." << endl;
            return;
        }

        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\n==============================" << endl;
        cout << "Driver Information" << endl;
        cout << "==============================" << endl;
        cout << "Driver ID: " << driverID << endl;
        cout << "Driver Name: " << name << endl;
        cout << fixed << setprecision(1);
        cout << "Rating: " << rating << endl;
        cout << "Completed Rides: " << assignedRides.size() << endl;

        for (const auto& ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    string riderID;
    string name;

    // Encapsulation: requested rides remain private
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(
        const string& id,
        const string& riderName
    )
        : riderID(id),
          name(riderName) {}

    void requestRide(const shared_ptr<Ride>& ride) {
        if (ride == nullptr) {
            cout << "Cannot request an invalid ride." << endl;
            return;
        }

        requestedRides.push_back(ride);
        cout << "Ride " << ride->getRideID()
             << " was requested successfully." << endl;
    }

    void viewRides() const {
        cout << "\n==============================" << endl;
        cout << "Rider Information" << endl;
        cout << "==============================" << endl;
        cout << "Rider ID: " << riderID << endl;
        cout << "Rider Name: " << name << endl;
        cout << "Requested Rides: " << requestedRides.size() << endl;

        for (const auto& ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

int main() {
    // Creating different ride objects
    shared_ptr<Ride> standardRide = make_shared<StandardRide>(
        "R1001",
        "Downtown",
        "Airport",
        12.5
    );

    shared_ptr<Ride> premiumRide = make_shared<PremiumRide>(
        "R1002",
        "University",
        "Convention Center",
        8.0
    );

    // Creating rider and requesting rides
    Rider rider("P2001", "Ranjith Bollam");
    rider.requestRide(standardRide);
    rider.requestRide(premiumRide);

    // Creating driver and assigning rides
    Driver driver("D3001", "Michael Johnson", 4.9);
    driver.addRide(standardRide);
    driver.addRide(premiumRide);

    // Display rider and driver information
    rider.viewRides();
    driver.getDriverInfo();

    // Polymorphism demonstration
    cout << "\n==============================" << endl;
    cout << "Polymorphism Demonstration" << endl;
    cout << "==============================" << endl;

    vector<shared_ptr<Ride>> rides = {
        standardRide,
        premiumRide
    };

    for (const auto& ride : rides) {
        ride->rideDetails();
    }

    return 0;
}