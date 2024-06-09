#pragma once

enum TypeTour {
    TypeA,
    TypeB
};

// Classe représentant une tour de défense
struct Tour {
    int puissance {};
    int portee {};
    float cadence {};
    TypeTour type;
};
