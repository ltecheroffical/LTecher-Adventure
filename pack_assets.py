import json
import os


def main():
    asset_file = open("gameassets.ltassets", "wb")
    
    asset_file.write(b"LTAssets")

    asset_parse_data = []
    
    with open(os.path.join("resources", "assetpackage.json"), "r") as f:
        asset_parse_data = json.load(f)

    for asset_data in asset_parse_data:
        asset_file.write(asset_data["id"].to_bytes(4, "little"))
        # Open the `asset_data["path"]` and get the position and data
        with open(os.path.join("resources", asset_data["path"]), "rb") as f:
            data = f.read()
            asset_file.write(len(data).to_bytes(4, "little"))
            asset_file.write(data)

    asset_file.close()


if __name__ == "__main__":
    main()
