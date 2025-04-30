#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>
using namespace std;

void setconsoleencoding() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}


// Классы для работы с рекламой
class AdManager;

class AdMaker {
private:
    int budget = 0;
    int fixedImpressions = 0;
public:
    void payForAds(int budget, AdManager& manager);
    void setFixedImpressions(int count, AdManager& manager);
    int getFrequency(int totalBudget) const;
    int getBudget() const { return budget; }
};

class AdManager {
private:
    int totalBudget = 0;
    map<AdMaker*, int> fixedImpressions;
public:
    void addAdMaker(AdMaker* maker, int impressions) {
        fixedImpressions[maker] = impressions;
    }
    int getRemainingImpressions(AdMaker* maker) {
        return fixedImpressions[maker];
    }
    void decrementImpressions(AdMaker* maker) {
        if (fixedImpressions[maker] > 0) fixedImpressions[maker]--;
    }
    void updateTotalBudget(int amount) {
        totalBudget += amount;
    }
    int getTotalBudget() const { return totalBudget; }
    map<AdMaker*, int> getImpressions() { return fixedImpressions; }
};

void AdMaker::payForAds(int budget, AdManager& manager) {
    this->budget = budget;
    manager.updateTotalBudget(budget);
}

void AdMaker::setFixedImpressions(int count, AdManager& manager) {
    fixedImpressions = count;
    manager.addAdMaker(this, count);
}

int AdMaker::getFrequency(int totalBudget) const {
    return (totalBudget > 0) ? (budget * 100 / totalBudget) : 0;
}

// Исправление: разделение блокировки и платного доступа
class Copyrighter {
private:
    map<string, bool> blockedVideos;   // Заблокированные видео
    map<string, bool> paidAccess;      // Платный доступ
public:
    void blockVideo(const string& videoId) {
        blockedVideos[videoId] = true;
    }
    void grantPaidAccess(const string& videoId) {
        paidAccess[videoId] = true;
    }
    bool isBlocked(const string& videoId) const {
        return blockedVideos.find(videoId) != blockedVideos.end();
    }
    bool hasPaidAccess(const string& videoId) const {
        return paidAccess.find(videoId) != paidAccess.end();
    }
};

class ContentMaker {
private:
    int maxAds = 0;
    bool isMonetizationBlocked = false;
public:
    void setAdRestriction(int max) {
        maxAds = (max > 2) ? 2 : max; // Ограничение до 2 вставок
    }
    float calculateEarnings(int views, float adCoefficient) const {
        return (isMonetizationBlocked) ? 0 : views * 0.01 * adCoefficient;
    }
    void blockMonetization() { isMonetizationBlocked = true; }
    int getAdRestriction() const { return maxAds; }
};

// Классы пользователей и видео
class User {
private:
    bool isPremium = false;
public:
    void subscribePremium() { isPremium = true; }
    bool hasPremium() const { return isPremium; }
    bool watchedMoreThan50Percent() const { return true; } // Пример реализации
};

class Video {
private:
    string id;
    ContentMaker* creator;
    Copyrighter* copyrightHolder = nullptr;
public:
    Video(const string& id, ContentMaker* creator) : id(id), creator(creator) {}
    void setCopyrightHolder(Copyrighter* holder) { copyrightHolder = holder; }
    bool isBlocked() const {
        return copyrightHolder ? copyrightHolder->isBlocked(id) : false;
    }
    bool requiresPayment() const {
        return copyrightHolder ? copyrightHolder->hasPaidAccess(id) : false;
    }
    ContentMaker* getCreator() const { return creator; }
};

// Логика показа видео
void showVideo(const User& user, const Video& video, AdManager& adManager) {
    if (video.isBlocked()) {
        cout << "[ОШИБКА] Видео заблокировано правообладателем." << endl;
        return;
    }

    if (video.requiresPayment() && !user.hasPremium()) {
        cout << "[ПЛАТНЫЙ ДОСТУП] Требуется подписка или оплата." << endl;
        return;
    }

    if (user.hasPremium()) {
        cout << "[ПРЕМИУМ] Показ без рекламы" << endl;
        return;
    }

    ContentMaker* creator = video.getCreator();
    int adCount = creator->getAdRestriction();
    vector<AdMaker*> selectedAds;

    // Выбор рекламы с учетом фиксированных показов
    for (auto& [maker, impressions] : adManager.getImpressions()) {
        if (impressions > 0) {
            selectedAds.push_back(maker);
            adManager.decrementImpressions(maker);
        }
    }

    // Ограничение до 2 вставок
    adCount = min(adCount, 2);
    cout << "Показ видео с " << adCount << " рекламными блоками" << endl;

    // Начисление дохода
    if (user.watchedMoreThan50Percent()) {
        float earnings = creator->calculateEarnings(1, adCount);
        cout << "Начислено создателю: $" << earnings << endl;
    }
}

// Пример использования
int main() {
    setconsoleencoding();
    AdManager manager;
    ContentMaker creator;
    creator.setAdRestriction(2);

    Copyrighter copyrightHolder;
    copyrightHolder.grantPaidAccess("videoPREMIUM"); // Платный доступ
    copyrightHolder.blockVideo("videoBLOCKED"); // Для блокировки

    Video video("video123", &creator);
    video.setCopyrightHolder(&copyrightHolder);

    Video video1("videoPREMIUM", &creator);
    video1.setCopyrightHolder(&copyrightHolder);

    Video video2("videoBLOCKED", &creator);
    video2.setCopyrightHolder(&copyrightHolder);

    User premiumUser;
    premiumUser.subscribePremium();

    User regularUser;

    cout <<"\n Премиумный пользователь:"<< endl;
    // Сценарий 1: Премиум-пользователь
    showVideo(premiumUser, video, manager);

    showVideo(premiumUser, video1, manager);

    showVideo(premiumUser, video2, manager);
    cout <<"\n Обычный пользователь:"<< endl;
    // Сценарий 2: Обычный пользователь
    showVideo(regularUser, video, manager);

    showVideo(regularUser, video1, manager);

    showVideo(regularUser, video2, manager);

}
