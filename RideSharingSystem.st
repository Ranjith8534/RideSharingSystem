"Ride Sharing System in GNU Smalltalk"

Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> rideID: anID
        pickup: aPickup
        dropoff: aDropoff
        distance: aDistance [
        
        ^self new
            initializeRideID: anID
            pickup: aPickup
            dropoff: aDropoff
            distance: aDistance
    ]

    initializeRideID: anID
        pickup: aPickup
        dropoff: aDropoff
        distance: aDistance [
        
        rideID := anID.
        pickupLocation := aPickup.
        dropoffLocation := aDropoff.
        distance := aDistance.
        ^self
    ]

    rideID [
        ^rideID
    ]

    distance [
        ^distance
    ]

    fare [
        self subclassResponsibility
    ]

    rideType [
        ^'General Ride'
    ]

    rideDetails [
        Transcript
            cr;
            show: '--- ', self rideType, ' ---'; cr;
            show: 'Ride ID: ', rideID; cr;
            show: 'Pickup Location: ', pickupLocation; cr;
            show: 'Drop-off Location: ', dropoffLocation; cr;
            show: 'Distance: ', distance printString, ' miles'; cr;
            show: 'Fare: $', self fare printString; cr
    ]
]


Ride subclass: StandardRide [

    fare [
        ^distance * 2.00
    ]

    rideType [
        ^'Standard Ride'
    ]
]


Ride subclass: PremiumRide [

    fare [
        ^distance * 3.50
    ]

    rideType [
        ^'Premium Ride'
    ]
]


Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> driverID: anID
        name: aName
        rating: aRating [
        
        ^self new
            initializeDriverID: anID
            name: aName
            rating: aRating
    ]

    initializeDriverID: anID
        name: aName
        rating: aRating [
        
        driverID := anID.
        name := aName.
        rating := aRating.
        assignedRides := OrderedCollection new.
        ^self
    ]

    addRide: aRide [
        assignedRides add: aRide
    ]

    getDriverInfo [
        Transcript
            cr;
            show: '=============================='; cr;
            show: 'Driver Information'; cr;
            show: '=============================='; cr;
            show: 'Driver ID: ', driverID; cr;
            show: 'Driver Name: ', name; cr;
            show: 'Rating: ', rating printString; cr;
            show: 'Completed Rides: ',
                assignedRides size printString; cr.

        assignedRides do: [:eachRide |
            eachRide rideDetails
        ]
    ]
]


Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> riderID: anID name: aName [
        ^self new
            initializeRiderID: anID
            name: aName
    ]

    initializeRiderID: anID name: aName [
        riderID := anID.
        name := aName.
        requestedRides := OrderedCollection new.
        ^self
    ]

    requestRide: aRide [
        requestedRides add: aRide.

        Transcript
            show: 'Ride ', aRide rideID,
                ' was requested successfully.';
            cr
    ]

    viewRides [
        Transcript
            cr;
            show: '=============================='; cr;
            show: 'Rider Information'; cr;
            show: '=============================='; cr;
            show: 'Rider ID: ', riderID; cr;
            show: 'Rider Name: ', name; cr;
            show: 'Requested Rides: ',
                requestedRides size printString; cr.

        requestedRides do: [:eachRide |
            eachRide rideDetails
        ]
    ]
]


"Main program"

| standardRide premiumRide rider driver rides |

standardRide := StandardRide
    rideID: 'R1001'
    pickup: 'Downtown'
    dropoff: 'Airport'
    distance: 12.5.

premiumRide := PremiumRide
    rideID: 'R1002'
    pickup: 'University'
    dropoff: 'Convention Center'
    distance: 8.0.

rider := Rider
    riderID: 'P2001'
    name: 'Ranjith Bollam'.

rider requestRide: standardRide.
rider requestRide: premiumRide.

driver := Driver
    driverID: 'D3001'
    name: 'Michael Johnson'
    rating: 4.9.

driver addRide: standardRide.
driver addRide: premiumRide.

rider viewRides.
driver getDriverInfo.

Transcript
    cr;
    show: '=============================='; cr;
    show: 'Polymorphism Demonstration'; cr;
    show: '=============================='; cr.

rides := OrderedCollection new.
rides add: standardRide.
rides add: premiumRide.

rides do: [:eachRide |
    eachRide rideDetails
].