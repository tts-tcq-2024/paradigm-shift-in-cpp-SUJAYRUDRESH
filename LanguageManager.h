#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "Language.h"

class LanguageManager {
public:
    void setLanguage(Language lang) { currentLanguage = lang; }
    Language getLanguage() const { return currentLanguage; }

private:
    Language currentLanguage;
};

#endif // LANGUAGEMANAGER_H
