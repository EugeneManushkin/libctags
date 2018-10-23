#include "include_internal_api.h"

#include <libctags/config.h>

#include <unordered_map>
#include <stdexcept>

namespace
{
  struct LanguageConfig
  {
    langType ID;
    bool Enabled;
    std::vector<LibCtags::Kind> Kinds;
  };

  LibCtags::Kind KindDefinitionToKind(kindDefinition const* def)
  {
    return {
      def->name,
      std::string(1, def->letter),
      def->description,
      !!def->enabled
    };
  }

  std::vector<LibCtags::Kind> GetLanguageKinds(langType language)
  {
    std::vector<LibCtags::Kind> result;
    auto count = countLanguageKinds(language);
    for (decltype(count) i = 0; i < count; ++i)
      result.push_back(KindDefinitionToKind(getLanguageKind(language, i)));

    return result;
  }

  class ConfigImpl : public LibCtags::Config
  {
  public:
    ConfigImpl()
    {
      auto count = static_cast<langType>(countParsers());
      for (langType id = 0; id < count; ++id)
      {
        if (!isLanguageVisible(id))
          continue;

        LanguageConfig config = {id, !!isLanguageEnabled(id), GetLanguageKinds(id)};
        Languages.insert(std::make_pair(std::string(getLanguageName(id)), config));
      }
    }

    virtual std::vector<std::string> GetLanguages() const override
    {
      std::vector<std::string> result;
      for (auto const &i : Languages)
        result.push_back(i.first);

      return result;
    }

    virtual std::vector<LibCtags::Kind> GetKinds(std::string const& language) const override
    {
      auto lang = Languages.find(language);
      if (lang == Languages.end())
        throw std::invalid_argument("Language not presented");

      return lang->second.Kinds;
    }

  private:
    std::unordered_map<std::string, LanguageConfig> Languages;
  };

}

namespace LibCtags
{
  std::unique_ptr<Config> GetConfig()
  {
    return std::unique_ptr<Config>(new ConfigImpl());
  }
}
