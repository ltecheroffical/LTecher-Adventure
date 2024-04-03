#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#define vec std::vector

inline std::map<int, vec<char>> assets;
inline std::map<int, char*> assets_raw;

inline std::map<int, unsigned int> asset_sizes;

inline void load_assets(char *path)
{
  std::ifstream assets_file(path);

  // Get file size
  assets_file.seekg(0, std::ios::end);
  std::streampos file_size = assets_file.tellg();
  assets_file.seekg(0, std::ios::beg);

  // Read entire file and save it into a vector
  vec<char> data((std::istreambuf_iterator<char>(assets_file)),
                  std::istreambuf_iterator<char>());

  assets_file.close(); 

  int bytes_left = 0;

  for (int i = 8; i < (int)file_size; i++)
  {
    bytes_left = (int)file_size - i;
    
    unsigned int asset_id = 0;
    unsigned int asset_size = 0;

    std::copy(&data[i], &data[i + sizeof(int)], reinterpret_cast<char*>(&asset_id));
    bytes_left -= sizeof(int);
    i += sizeof(int);
    std::copy(&data[i], &data[i + sizeof(int)], reinterpret_cast<char*>(&asset_size));
    bytes_left -= sizeof(int);
    i += sizeof(int);

    vec<char> asset_data;
    char     *asset_data_raw = (char*)malloc(asset_size);

    bool can_use_raw_asset_data = true;

    if (asset_data_raw == NULL)
    {
      // The OS didn't give us the memory we requested
      can_use_raw_asset_data = false;
    }
    asset_data.reserve(asset_size);
    
    if (bytes_left < asset_size)
    {
      // The assets may have been used as a buffer overflow attack
      throw((char*)"Asset id #" + std::to_string(asset_id) + " is too large!");
    }

    std::copy(&data[i], &data[i + asset_size], asset_data.begin());

    if (can_use_raw_asset_data)
    {
      std::copy(&data[i], &data[i + asset_size], asset_data_raw);
    }

#if PRODUCTION_BUILD == 0
    std::cout << "Asset Loaded! " << "Asset ID: " << asset_id << " Size: " << asset_size << std::endl;
#endif

    assets.try_emplace((int)asset_id, asset_data);

    if (can_use_raw_asset_data)
    {
      assets_raw.try_emplace((int)asset_id, asset_data_raw);
    }
    asset_sizes.try_emplace((int)asset_id, asset_size); 

    // Skip past the asset data
    i += asset_size - 1;
  }
}

inline void unload_assets()
{
  // Free all the assets
  for (auto it = assets_raw.begin(); it != assets_raw.end(); it++)
  {
    free(it->second);
  }
}
