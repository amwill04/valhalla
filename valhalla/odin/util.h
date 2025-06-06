#ifndef VALHALLA_ODIN_UTIL_H_
#define VALHALLA_ODIN_UTIL_H_

#include <valhalla/odin/narrative_dictionary.h>

#include <cstdint>
#include <locale>
#include <string>
#include <unordered_map>

namespace valhalla {
namespace odin {

const bool kLimitByConseuctiveCount = true;
constexpr uint32_t kElementMaxCount = 4;
constexpr uint32_t kVerbalAlertElementMaxCount = 1;
constexpr uint32_t kVerbalPreElementMaxCount = 2;
constexpr uint32_t kVerbalPostElementMaxCount = 2;
const std::string kVerbalDelim = ", ";

struct Bcp47Locale {
  std::string langtag;
  std::string language;
  std::string script;
  std::string region;
  std::string privateuse;

  std::string get_lang_script() {
    std::string lang_script = language;
    if (!script.empty()) {
      lang_script += "-";
      lang_script += script;
    }
    return lang_script;
  }

  bool valid() {
    return !langtag.empty();
  }
};

/**
 * Returns the specified item surrounded with quotes.
 * @param item  specified text to surround with quotes
 * @return the specified item surrounded with quotes.
 */
std::string GetQuotedString(const std::string& item);

bool IsSimilarTurnDegree(uint32_t path_turn_degree,
                         uint32_t intersecting_turn_degree,
                         bool is_right,
                         uint32_t turn_degree_threshold = 40);

/**
 * Get the time from the provided date.
 * date_time is in the format of 2015-05-06T08:00
 * @param   date_time in the format of 2015-05-06T08:00
 * @param   locale locale
 * @return  Returns the formatted time based on the locale.
 */
std::string get_localized_time(const std::string& date_time, const std::locale& locale);

/**
 * Get the date from the provided date.
 * date_time is in the format of 2015-05-06T08:00
 * @param   date_time in the format of 2015-05-06T08:00
 * @param   locale locale
 * @return  Returns the formatted date based on the locale.
 */
std::string get_localized_date(const std::string& date_time, const std::locale& locale);

using locales_singleton_t = std::unordered_map<std::string, std::shared_ptr<NarrativeDictionary>>;
/**
 * Returns locale strings mapped to NarrativeDictionaries containing parsed narrative information
 *
 * @return the map of locales to NarrativeDictionaries
 */
const locales_singleton_t& get_locales();

/**
 * Returns locale strings mapped to json strings defining the dictionaries
 *
 * @return the map of locales to json strings
 */
const std::unordered_map<std::string, std::string>& get_locales_json();

Bcp47Locale parse_string_into_locale(const std::string& locale_string);

/**
 * Returns the string representation for a turn lane direction.
 *
 * @return lane direction string.
 */
std::string turn_lane_direction(uint16_t turn_lane);

size_t get_word_count(const std::string& street_name);

std::size_t strlen_utf8(const std::string& str);

} // namespace odin
} // namespace valhalla
#endif // VALHALLA_ODIN_UTIL_H_
