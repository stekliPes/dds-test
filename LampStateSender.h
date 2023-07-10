#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

class LampState;

using namespace eprosima::fastdds::dds;

class LampStateSender
{
    public:
        LampStateSender();
        virtual ~LampStateSender();

        void send(LampState &);
    private:
       

        DomainParticipant *m_domainParticipantPtr;
        Publisher *m_publisherPtr;
        Topic *m_topicPtr;
        DataWriter *m_dataWriterPtr;
        TypeSupport m_type;
};