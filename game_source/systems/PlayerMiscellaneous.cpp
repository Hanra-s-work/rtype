#include "PlayerMiscellaneous.hpp"
#include "Registry.hpp"
#include "IndexedZipper.hpp"
#include "PlayerInfo.hpp"

std::size_t getIdByClientId(Registry &r, const unsigned int client_id)
{
    auto &infos = r.get_components<PlayerInfo>();
    for (auto &&[idx, info] : IndexedZipper(infos))
    {
        if (info->id == client_id)
            return idx;
    }
    return -1;
}