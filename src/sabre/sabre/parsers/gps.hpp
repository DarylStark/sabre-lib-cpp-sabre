#pragma once

#include "../models/geo.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace sabre
{
    namespace parsers
    {
        using namespace sabre::models::geo;

        /**
         * @brief NMEA sentence parser for extracting position data.
         */
        class NmeaParser
        {
        private:
            Position _last_position; /**< Last parsed position. */
            std::map<std::string, std::string>
                _scentences; /**< Buffered sentences. */

            /**
             * @brief Extracts the sentence type (e.g., RMC, GGA).
             * @param scentence The NMEA sentence.
             * @return The type string.
             */
            std::string _get_type(std::string scentence) const;

            /**
             * @brief Extracts the talker ID (e.g., GP, GN).
             * @param scentence The NMEA sentence.
             * @return The talker string.
             */
            std::string _get_talker(std::string scentence) const;

            bool _is_valid_checksum(const std::string &scentence) const;

            /**
             * @brief Parse RMC sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_rmc(std::string scentence);

            /**
             * @brief Parse GLL sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gll(std::string scentence);

            /**
             * @brief Parse GGA sentence.
             * @param scentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gga(std::string scentence);

            /**
             * @brief Split a sentence into fields.
             * @param scentence The NMEA sentence.
             * @return Vector of fields.
             */
            std::vector<std::string> _get_fields(std::string scentence) const;

            /**
             * @brief Helper to extract coordinates from fields.
             * @param fields The split fields.
             * @param lat_idx Latitude field index.
             * @param lat_dir_idx Latitude direction field index.
             * @param lon_idx Longitude field index.
             * @param lon_dir_idx Longitude direction field index.
             * @param out_position Output position.
             * @return True if extraction was successful.
             */
            bool _extract_position_from_fields(
                const std::vector<std::string> &fields, size_t lat_idx,
                size_t lat_dir_idx, size_t lon_idx, size_t lon_dir_idx,
                Position &out_position) const;

            void _update_last_position(Position &new_position);

        public:
            /**
             * @brief Default constructor.
             */
            NmeaParser();

            /**
             * @brief Add a sentence to the buffer.
             * @param scentence The NMEA sentence.
             */
            void add_scentence(const std::string &scentence);

            /**
             * @brief Parse buffered sentences and update last position.
             */
            void parse();

            /**
             * @brief Get the last parsed position.
             * @return Last position.
             */
            Position get_last_position() const;

            /**
             * @brief Get the number of buffered sentences.
             * @return Sentence count.
             */
            size_t get_scentence_count() const;
        };
    } // namespace parsers
} // namespace sabre