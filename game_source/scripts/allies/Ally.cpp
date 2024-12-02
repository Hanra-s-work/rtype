#include "Ally.hpp"
#include "Scene.hpp"

Ally::Ally(const std::string& username, int initialHealth)
        : username(username), health(initialHealth), GameObject("", "Ally") {}

void Ally::OnCreate() {
    std::cout << "Ally \"" << username << "\" has been created with " << health << " health points.\n";
}

void Ally::Update() {
    std::cout << "Updating Ally \"" << username << "\".\n";
}

void Ally::TakeDamage(int damage) {
    health -= damage;

    if (health <= 0) {
        Scene::DestroyObject(*this);
    }
}
