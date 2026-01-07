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
        /**
         * @brief NMEA sentence parser for extracting position data.
         */
        class NmeaParser
        {
        private:
            sabre::models::geo::Position
                _last_position; /**< Last parsed position. */
            std::map<std::string, std::string>
                _sentences; /**< Buffered sentences. */

            /**
             * @brief Extracts the sentence type (e.g., RMC, GGA).
             * @param sentence The NMEA sentence.
             * @return The type string.
             */
            std::string _get_type(const std::string &sentence) const;

            /**
             * @brief Extracts the talker ID (e.g., GP, GN).
             * @param sentence The NMEA sentence.
             * @return The talker string.
             */
            std::string _get_talker(const std::string &sentence) const;

            bool _is_valid_checksum(const std::string &sentence) const;

            /**
             * @brief Parse RMC sentence.
             * @param sentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_rmc(const std::string &sentence);

            /**
             * @brief Parse GLL sentence.
             * @param sentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gll(const std::string &sentence);

            /**
             * @brief Parse GGA sentence.
             * @param sentence The NMEA sentence.
             * @return True if valid and parsed.
             */
            bool _parse_gga(const std::string &sentence);

            /**
             * @brief Split a sentence into fields.
             * @param sentence The NMEA sentence.
             * @return Vector of fields.
             */
            std::vector<std::string>
            _get_fields(const std::string &sentence) const;

            /**
             * @brief Helper to extract coordinates from fields.
             * @param fields The split fields.
             * @param latIndex Latitude field index.
             * @param latDirIndex Latitude direction field index.
             * @param lonIndex Longitude field index.
             * @param lonDirIndex Longitude direction field index.
             * @param outPosition Output position.
             * @return True if extraction was successful.
             */
            bool _extractPositionFromFields(
                const std::vector<std::string> &fields, size_t latIndex,
                size_t latDirIndex, size_t lonIndex, size_t lonDirIndex,
                sabre::models::geo::Position &outPosition) const;

            void _updateLastPosition(sabre::models::geo::Position &newPosition);

        public:
            /**
             * @brief Add a sentence to the buffer.
             * @param sentence The NMEA sentence.
             */
            void addSentence(const std::string &sentence);

            /**
             * @brief Parse buffered sentences and update last position.
             */
            void parse();

            /**
             * @brief Get the last parsed position.
             * @return Last position.
             */
            sabre::models::geo::Position getLastPosition() const;

            /**
             * @brief Get the number of buffered sentences.
             * @return Sentence count.
             */
            size_t getSentenceCount() const;
        };
    } // namespace parsers
} // namespace sabre