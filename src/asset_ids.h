#include <iostream>
#include <fstream>
#include <map>

inline std::map<int, char*> assets;
inline std::map<int, unsigned int> asset_sizes;

inline void load_assets(char *path)
{
  std::ifstream assets_file(path);

  // Get file size
  assets_file.seekg(0, std::ios::end);
  std::streampos file_size = assets_file.tellg();
  assets_file.seekg(0, std::ios::beg);

  // Read entire file and save it into char*
  char *data = (char*)malloc(file_size);
  
  assets_file.read(data, file_size);
  assets_file.close(); 

  int bytes_left = 0;

  for (int i = 8; i < (int)file_size; i++)
  {
    bytes_left = (int)file_size - i;
    
    unsigned int asset_id = 0;
    unsigned int asset_size = 0;

    memcpy(&asset_id, data + i, sizeof(int));
    i += sizeof(int);
    memcpy(&asset_size, data + i, sizeof(int));
    i += sizeof(int);

    char *asset_data = (char*)malloc(asset_size);

    bytes_left -= (sizeof(int) * 2);
    
    if (bytes_left < asset_size)
    {
      // The assets may have been used as a buffer overflow attack
      free(data);
      throw((char*)"Asset too large!");
    }

    memcpy(asset_data, data + i, asset_size);

    assets.try_emplace((int)asset_id, asset_data);
    asset_sizes.try_emplace((int)asset_id, asset_size);

    // Skip past the asset data
    i += asset_size - 1;
  }
  free(data);
}

inline void unload_assets()
{
  // Free all the assets
  for (auto it = assets.begin(); it != assets.end(); it++)
  {
    free(it->second);
  }
}
