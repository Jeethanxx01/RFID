/*
 * MIT License
 * Copyright (c) 2018 Brian T. Park
 */

#ifndef ACE_TIME_TIME_OFFSET_H
#define ACE_TIME_TIME_OFFSET_H

#include <stdint.h>

class Print;

namespace ace_time {

// These functions need to set the mMinutes and it seemed inefficient to
// go through the factory method and assignment operator, so I expose
// setMinutes() to them for efficiency.
class TimeOffset;
namespace time_offset_mutation {
void incrementHour(TimeOffset& offset);
void increment15Minutes(TimeOffset& offset);
}

/**
 * A thin wrapper that represents a time offset from a reference point, usually
 * 00:00 at UTC, but not always. Use one of the static factory methods to
 * create an instance. For example, each of the following creates a TimeOffset
 * of -08:00:
 *
 * @code{.cpp}
 * TimeOffset tz = TimeOffset::forHours(-8);
 * TimeOffset tz = TimeOffset::forHourMinute(-8, 0);
 * TimeOffset tz = TimeOffset::forMinutes(-480);
 * TimeOffset tz = TimeOffset::forOffsetString("-08:00");
 * @endcode
 *
 * You can use the default constructor to create a +00:00 TimeOffset:
 * @code{.cpp}
 * TimeOffset offset;
 * @endcode
 *
 * The current implementation has a resolution of 1-minute (using an internal
 * int16_t type). The previous implementation (< v0.7) had a resolution of
 * 15-minutes (using an internal int8_t type) because that was sufficient to
 * handle all current timezones for years >= 2018 (determined by looking at
 * https://en.wikipedia.org/wiki/List_of_UTC_time_offsets, and the TZ Database
 * zonefiles itself through the tzcompiler.py script). However, 15-minute
 * resolution is not sufficient to handle a handful of timezones in the past
 * (years 2000 to 2011 or so). So I changed the implementation to use 2 bytes
 * to handle 1-minute resolution.
 *
 * This class does NOT know about the TZ Database (aka Olson database)
 * https://en.wikipedia.org/wiki/Tz_database. That functionality is implemented
 * in the TimeZone class.
 */
class TimeOffset {
  public:
    /** Sentinel value that represents an error. */
    static const int16_t kErrorMinutes = INT16_MIN;

    /**
     * Create TimeOffset with the corresponding hour offset. For example,
     * -08:00 is 'forHours(-8)'.
     */
    static TimeOffset forHours(int8_t hours) {
      return TimeOffset::forMinutes(hours * 60);
    }

    /**
     * Create TimeOffset from (hour, minute) offset. If the offset is negative,
     * then the negative sign must be added to both the hour and minute
     * components. This allows a negative offset of less than -01:00 to be
     * created. For example, -07:30 is created by 'forHourMinute(-7, -30)' (not
     * 'forHourMinute(-7, 30), and -00:15 is created by 'forHourMinute(0,
     * -15)'.
     */
    static TimeOffset forHourMinute(int8_t hour, int8_t minute) {
      int16_t minutes = hour * 60 + minute;
      return TimeOffset(minutes);
    }

    /** Create TimeOffset from minutes from 00:00. */
    static TimeOffset forMinutes(int16_t minutes) {
      return TimeOffset(minutes);
    }

    /**
     * Create from an offset string ("-07:00" or "+01:00"). Intended mostly
     * for testing purposes.
     * Returns TimeOffset::forError() if a parsing error occurs.
     */
    static TimeOffset forOffsetString(const char* offsetString);

    /**
     * Variant of forOffsetString() that updates the string pointer to the next
     * unprocessed character. The resulting pointer can be passed to another
     * forDateStringInternal() method to chain the parsing.
     *
     * This method assumes that the offsetString is sufficiently long.
     * Returns TimeOffset::forError() if a parsing error occurs.
     */
    static TimeOffset forOffsetStringChainable(const char*& offsetString);

    /** Return an error indicator. */
    static TimeOffset forError() { return TimeOffset(kErrorMinutes); }

    /** Constructor. Create a time offset of 0. */
    explicit TimeOffset() {}

    /** Return the time offset as minutes. */
    int16_t toMinutes() const {
      return mMinutes;
    }

    /** Return the time offset as seconds. */
    int32_t toSeconds() const {
      return (int32_t) 60 * toMinutes();
    }

    /**
     * Extract hour and minute representation of the offset. This the inverse
     * of 'forHourMinute()'. If the TimeOffset is negative, then both the
     * hour and minute components will contain the negative sign.
     */
    void toHourMinute(int8_t& hour, int8_t& minute) const {
      hour = mMinutes / 60;
      minute = mMinutes % 60;
    }

    /**
     * Returns true if offset is 00:00. If this represents a time zone, then
     * isZero means that it is UTC. If this represents a DST delta offset, then
     * isZero means that the time zone is in standard time.
     */
    bool isZero() const { return mMinutes == 0; }

    /** Return true if this TimeOffset represents an error. */
    bool isError() const {
      return mMinutes == kErrorMinutes;
    }

    /** Print the human readable string. For example, "-08:00". */
    void printTo(Print& printer) const;

    // Use default copy constructor and assignment operator.
    TimeOffset(const TimeOffset&) = default;
    TimeOffset& operator=(const TimeOffset&) = default;

  private:
    friend bool operator==(const TimeOffset& a, const TimeOffset& b);

    // Give access to setMinutes()
    friend void time_offset_mutation::incrementHour(TimeOffset& offset);
    friend void time_offset_mutation::increment15Minutes(TimeOffset& offset);

    /** Length of UTC offset string (e.g. "-07:00", "+01:30"). */
    static const uint8_t kTimeOffsetStringLength = 6;

    /** Constructor. Create a time offset from the offset minutes. */
    explicit TimeOffset(int16_t minutes):
        mMinutes(minutes) {}

    /** Set the offset minutes. */
    void setMinutes(int16_t minutes) {
      mMinutes = minutes;
    }

    /**
     * Time offset minutes from UTC. In theory, the minutes can range from
     * [-32768, 32767]. But the value of -32768 is used to represent an
     * internal error, causing isError() to return true so the valid range is
     * [-32767, 32767].
     */
    int16_t mMinutes = 0;
};

inline bool operator==(const TimeOffset& a, const TimeOffset& b) {
  return a.mMinutes == b.mMinutes;
}

inline bool operator!=(const TimeOffset& a, const TimeOffset& b) {
  return ! (a == b);
}

}

#endif
