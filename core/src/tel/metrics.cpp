#include <algorithm>
#include <deque>
#include <map>
#include <mutex>
#include <utility>
#include <vector>

#include <cubos/core/tel/logging.hpp>
#include <cubos/core/tel/metrics.hpp>

using cubos::core::tel::Metrics;

namespace
{
    /// @brief Private type which stores the state of the metrics pool.
    struct State
    {
        std::map<std::string, std::deque<double>> mMetrics;     ///< Collection of metrics.
        std::vector<std::string> mNames;                        ///< Collection of unique metric names.
        std::size_t mMaxEntries{CUBOS_CORE_METRIC_MAX_ENTRIES}; ///< Maximum number of entries each metric can store.
        mutable std::mutex mMutex;                              ///< Mutex for thread-safe access to the metrics.
    };
} // namespace

/// @brief Metrics pool state singleton. Guarantees it is initialized exactly once, when needed.
/// @return Metrics pool.
static State& state()
{
    static State instance{};
    return instance;
}

void Metrics::metric(const std::string& name, const double metric)
{
    std::string fullName = SpanManager::current().path + ":" + name;

    std::lock_guard<std::mutex> lock(state().mMutex);

    if (state().mMetrics[fullName].size() >= state().mMaxEntries)
    {
        state().mMetrics[fullName].pop_back();
    }

    state().mMetrics[fullName].push_back(metric);

    // add metric name if new
    if (std::find(state().mNames.cbegin(), state().mNames.cend(), fullName) == state().mNames.end())
    {
        state().mNames.emplace_back(fullName);
    }
}

std::size_t Metrics::size()
{
    std::lock_guard<std::mutex> lock(state().mMutex);

    return state().mNames.size();
}

std::size_t Metrics::sizeByName(const std::string& name)
{
    std::lock_guard<std::mutex> lock(state().mMutex);

    if (!state().mMetrics.contains(name))
    {
        return 0;
    }

    return state().mMetrics.at(name).size();
}

void Metrics::clear()
{
    std::lock_guard<std::mutex> lock(state().mMutex);

    state().mMetrics.clear();
    state().mNames.clear();
}

void Metrics::setMaxEntries(std::size_t n)
{
    state().mMaxEntries = n;
}

bool Metrics::readValue(const std::string& name, double& value, std::size_t& offset)
{
    std::lock_guard<std::mutex> lock(state().mMutex);

    if (!state().mMetrics.contains(name))
    {
        return false;
    }

    if (offset >= state().mMetrics.at(name).size())
    {
        return false;
    }

    auto test = state().mMetrics;
    value = state().mMetrics.at(name).at(offset);
    offset++;
    test.clear();
    return true;
}

bool Metrics::readName(std::string& name, size_t& seenCount)
{
    std::lock_guard<std::mutex> lock(state().mMutex);

    if (seenCount >= state().mNames.size())
    {
        return false;
    }

    name = state().mNames.at(seenCount);
    seenCount++;
    return true;
}