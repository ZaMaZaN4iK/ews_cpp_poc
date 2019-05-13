#include <ews/ews.hpp>

#include <exception>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    ews::set_up();

    try {
        const auto basicCreds = ews::basic_credentials("qa@inovwave1.onmicrosoft.com", "Xod25733");

        auto service = ews::service("https://outlook.office365.com/ews/Exchange.asmx",
                                    basicCreds);

        auto search_expression =
                ews::contains(ews::item_property_path::subject, "150 MB",
                              ews::containment_mode::substring,
                              ews::containment_comparison::ignore_case);

        ews::distinguished_folder_id inbox = ews::standard_folder::inbox;
        auto items = service.find_item(inbox, search_expression);

        for(const auto& item : items)
        {
            auto message = service.get_message(item);
            auto attachments = message.get_attachments();

            /*for(const auto& attachment : attachments)
            {*/
                //std::cout << attachments.back().content() << std::endl;
                std::fstream attachment_file;
                attachment_file.open("/home/zamazan4ik/OpenSource/ews_cpp_poc/attach.txt", std::ios_base::out);
                attachment_file << service.get_attachment(attachments.back().id()).content();
                attachment_file.close();
            //}

        }

        /*auto message = ews::message();
        message.set_subject("Test mail from outer space");
        std::vector<ews::mailbox> recipients{ ews::mailbox("qa@inovwave1.onmicrosoft.com") };
        message.set_to_recipients(recipients);
        auto text = ews::body("ようこそ (Welcome!)\n\nThis is a test.\n");
        message.set_body(text);
        service.create_item(message, ews::message_disposition::send_and_save_copy);*/
    } catch (std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    ews::tear_down();
    return 0;
}
