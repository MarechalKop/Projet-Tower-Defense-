#pragma once

enum TypeTour {
    TypeA,
    TypeB
};

struct Tour {
    int puissance {};
    int portee {};
    float cadence {};
    TypeTour type;
};
