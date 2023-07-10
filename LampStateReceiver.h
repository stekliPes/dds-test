#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

#include "shared/LampState.h"

class LampState;

using namespace eprosima::fastdds::dds;

class LampStateListener : public DataReaderListener
{
    public:
        LampStateListener(){};
        virtual ~LampStateListener(){};

        void on_data_available(DataReader* reader) override;
        
    private:
        LampState m_lampState;
        SampleInfo m_sampleInfo;
};

class LampStateReceiver
{
    public:
        LampStateReceiver();
        virtual ~LampStateReceiver();
    private:
       

        DomainParticipant *m_domainParticipantPtr;
        Subscriber *m_subscriberPtr;
        Topic *m_topicPtr;
        DataReader *m_dataReaderPtr;
        TypeSupport m_type;
        LampStateListener m_listener;
};

