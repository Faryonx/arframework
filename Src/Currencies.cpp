#include <Currencies.hpp>
#include <Text.hpp>

#ifdef __MWERKS__
# pragma pcrelconstdata on
#endif

namespace ArsLexis{

    enum {
        currencyAbbrevLength    =4,
        currencyNameLength      =55,
        currencyCoutriesLength  =106
    };
    
    typedef const char_t CurrencyAbbrevField_t[currencyAbbrevLength];
    typedef const char_t CurrencyNameField_t[currencyNameLength];
    typedef const char_t CurrencyCountriesField_t[currencyCoutriesLength];
    
    struct CurrencyArrayEntry {
        const CurrencyAbbrevField_t abbrev;
        const CurrencyNameField_t name;
        const CurrencyCountriesField_t countries;
    };

    static const CurrencyArrayEntry currencies[CURRENCY_COUNT]=
    {
        {_T("USD"), _T("United States Dollars"), _T("Ecuador, Micronesia (Federated States of), Palau") },
        {_T("EUR"), _T("Euro"), _T("Austria, Belgium, Finland, France, Greece, Eire (Ireland), Italy, Luxembourg, Martinique, Portugal, Spain") },
        {_T("JPY"), _T("Yen"), _T("Japan") },
        {_T("GBP"), _T("Pounds"), _T("Britain (United Kingdom)") },
        {_T("AED"), _T("Dirhams"), _T("United Arab Emirates") },
        {_T("AFA"), _T("Afghanis"), _T("Afghanistan") },
        {_T("ALL"), _T("Leke"), _T("Albania") },
        {_T("AMD"), _T("Drams"), _T("Armenia") },
        {_T("ANG"), _T("Netherlands Antilles Guilders"), _T("Aruba, Aruba") },
        {_T("AOA"), _T("Kwanza"), _T("Angola") },
        {_T("ARS"), _T("Pesos"), _T("Argentina") },
        {_T("AUD"), _T("Dollars"), _T("Australia") },
        {_T("AZM"), _T("Manats"), _T("Azerbaijan") },
        {_T("BAM"), _T("Convertible Marka"), _T("Bosnia and Herzegovina") },
        {_T("BBD"), _T("Dollars"), _T("Barbados") },
        {_T("BDT"), _T("Taka"), _T("Bangladesh") },
        {_T("BGN"), _T("Leva"), _T("Bulgaria") },
        {_T("BHD"), _T("Dinars"), _T("Bahrain") },
        {_T("BIF"), _T("Francs"), _T("Burundi") },
        {_T("BMD"), _T("Dollars"), _T("Bermuda") },
        {_T("BND"), _T("Dollars"), _T("Brunei Darussalam") },
        {_T("BOB"), _T("Bolivianos"), _T("Bolivia") },
        {_T("BRL"), _T("Real"), _T("Brazil") },
        {_T("BSD"), _T("Dollars"), _T("Bahamas") },
        {_T("BWP"), _T("Pulas"), _T("Botswana") },
        {_T("BYR"), _T("Rubles"), _T("Belarus") },
        {_T("BZD"), _T("Dollars"), _T("Belize") },
        {_T("CAD"), _T("Dollars"), _T("Canada") },
        {_T("CHF"), _T("Switzerland Francs"), _T("Liechtenstein") },
        {_T("CLP"), _T("Pesos"), _T("Chile") },
        {_T("CNY"), _T("Yuan Renminbi"), _T("China") },
        {_T("COP"), _T("Pesos"), _T("Colombia") },
        {_T("CRC"), _T("Colones"), _T("Costa Rica") },
        {_T("CVE"), _T("Escudos"), _T("Cape Verde") },
        {_T("CYP"), _T("Pounds"), _T("Cyprus") },
        {_T("CZK"), _T("Koruny"), _T("Czech Republic") },
        {_T("DJF"), _T("Francs"), _T("Djibouti") },
        {_T("DKK"), _T("Kroner"), _T("Denmark") },
        {_T("DOP"), _T("Pesos"), _T("Dominican Republic") },
        {_T("DZD"), _T("Dinars"), _T("Algeria") },
        {_T("EEK"), _T("Krooni"), _T("Estonia") },
        {_T("EGP"), _T("Pounds"), _T("Egypt") },
        {_T("ETB"), _T("Ethiopia Birr"), _T("Eritrea, Eritrea") },
        {_T("FJD"), _T("Dollars"), _T("Fiji") },
        {_T("GEL"), _T("Lari"), _T("Georgia") },
        {_T("GHC"), _T("Cedis"), _T("Ghana") },
        {_T("GMD"), _T("Dalasi"), _T("Gambia") },
        {_T("GTQ"), _T("Quetzales"), _T("Guatemala") },
        {_T("GYD"), _T("Dollars"), _T("Guyana") },
        {_T("HKD"), _T("Dollars"), _T("Hong Kong") },
        {_T("HNL"), _T("Lempiras"), _T("Honduras") },
        {_T("HRK"), _T("Kuna"), _T("Croatia") },
        {_T("HTG"), _T("Gourdes"), _T("Haiti") },
        {_T("HUF"), _T("Forint"), _T("Hungary") },
        {_T("IDR"), _T("Indonesia Rupiahs"), _T("East Timor") },
        {_T("ILS"), _T("New Shekels"), _T("Israel") },
        {_T("INR"), _T("India Rupeess"), _T("Bhutan") },
        {_T("IQD"), _T("Dinars"), _T("Iraq") },
        {_T("IRR"), _T("Rials"), _T("Iran") },
        {_T("ISK"), _T("Kronur"), _T("Iceland") },
        {_T("JMD"), _T("Dollars"), _T("Jamaica") },
        {_T("JOD"), _T("Dinars"), _T("Jordan") },
        {_T("KES"), _T("Shillings"), _T("Kenya") },
        {_T("KGS"), _T("Soms"), _T("Kyrgyzstan") },
        {_T("KMF"), _T("Francs"), _T("Comoros") },
        {_T("KPW"), _T("Won"), _T("Korea (North)") },
        {_T("KWD"), _T("Dinars"), _T("Kuwait") },
        {_T("LAK"), _T("Kips"), _T("Laos") },
        {_T("LBP"), _T("Pounds"), _T("Lebanon") },
        {_T("LKR"), _T("Rupees"), _T("Sri Lanka") },
        {_T("LRD"), _T("Dollars"), _T("Liberia") },
        {_T("LSL"), _T("Maloti"), _T("Lesotho") },
        {_T("LTL"), _T("Litai"), _T("Lithuania") },
        {_T("LVL"), _T("Lati"), _T("Latvia") },
        {_T("MAD"), _T("Dirhams"), _T("Morocco") },
        {_T("MDL"), _T("Lei"), _T("Moldova") },
        {_T("MGA"), _T("Ariary"), _T("Madagascar") },
        {_T("MMK"), _T("Kyats"), _T("Burma (Myanmar)") },
        {_T("MNT"), _T("Tugriks"), _T("Mongolia") },
        {_T("MRO"), _T("Ouguiyas"), _T("Mauritania") },
        {_T("MTL"), _T("Liri"), _T("Malta") },
        {_T("MUR"), _T("Rupees"), _T("Mauritius") },
        {_T("MWK"), _T("Kwachas"), _T("Malawi") },
        {_T("MXN"), _T("Pesos"), _T("Mexico") },
        {_T("MYR"), _T("Ringgits"), _T("Malaysia") },
        {_T("MZM"), _T("Meticais"), _T("Mozambique") },
        {_T("NAD"), _T("Dollars"), _T("Namibia") },
        {_T("NGN"), _T("Nairas"), _T("Nigeria") },
        {_T("NIO"), _T("Gold Cordobas"), _T("Nicaragua, Nicaragua") },
        {_T("NOK"), _T("Norway Kroner"), _T("Bouvet Island") },
        {_T("NPR"), _T("Rupees"), _T("Nepal") },
        {_T("NZD"), _T("New Zealand Dollars"), _T("Cook Islands") },
        {_T("OMR"), _T("Rials"), _T("Oman") },
        {_T("PAB"), _T("Balboa"), _T("Panama") },
        {_T("PEN"), _T("Nuevos Soles"), _T("Peru, Peru") },
        {_T("PGK"), _T("Kina"), _T("Papua New Guinea") },
        {_T("PHP"), _T("Pesos"), _T("Philippines") },
        {_T("PKR"), _T("Rupees"), _T("Pakistan") },
        {_T("PLN"), _T("Zlotych"), _T("Poland") },
        {_T("PYG"), _T("Guarani"), _T("Paraguay") },
        {_T("QAR"), _T("Rials"), _T("Qatar") },
        {_T("ROL"), _T("Lei"), _T("Romania") },
        {_T("RUR"), _T("Rubles"), _T("Russia, Tajikistan") },
        {_T("RWF"), _T("Francs"), _T("Rwanda") },
        {_T("SAR"), _T("Riyals"), _T("Saudi Arabia") },
        {_T("SBD"), _T("Dollars"), _T("Solomon Islands") },
        {_T("SCR"), _T("Rupees"), _T("Seychelles") },
        {_T("SDD"), _T("Dinars"), _T("Sudan") },
        {_T("SEK"), _T("Kronor"), _T("Sweden") },
        {_T("SGD"), _T("Dollars"), _T("Singapore") },
        {_T("SIT"), _T("Tolars"), _T("Slovenia") },
        {_T("SLL"), _T("Leones"), _T("Sierra Leone") },
        {_T("SRD"), _T("Dollars"), _T("Suriname") },
        {_T("SVC"), _T("Colones"), _T("El Salvador") },
        {_T("SYP"), _T("Pounds"), _T("Syria") },
        {_T("SZL"), _T("Emalangeni"), _T("Swaziland") },
        {_T("THB"), _T("Baht"), _T("Thailand") },
        {_T("TMM"), _T("Manats"), _T("Turkmenistan") },
        {_T("TND"), _T("Dinars"), _T("Tunisia") },
        {_T("TOP"), _T("Pa'anga"), _T("Tonga") },
        {_T("TRL"), _T("Liras"), _T("Turkey") },
        {_T("TWD"), _T("New Dollars"), _T("Taiwan") },
        {_T("TZS"), _T("Shillings"), _T("Tanzania") },
        {_T("UAH"), _T("Hryvnia"), _T("Ukraine") },
        {_T("UGX"), _T("Shillings"), _T("Uganda") },
        {_T("UYU"), _T("Pesos"), _T("Uruguay") },
        {_T("UZS"), _T("Sums"), _T("Uzbekistan") },
        {_T("VEB"), _T("Bolivares"), _T("Venezuela") },
        {_T("VUV"), _T("Vatu"), _T("Vanuatu") },
        {_T("WST"), _T("Tala"), _T("Western Samoa (Samoa)") },
        {_T("XAF"), _T("Communaut&eacute; Financi&egrave;re Africaine Francs"), _T("Cameroon, Central African Republic, Chad, Congo/Brazzaville, Equatorial Guinea, Gabon") },
        {_T("XCD"), _T("East Caribbean Dollars"), _T("Antigua and Barbuda, Grenada") },
        {_T("XOF"), _T("Communaut&eacute; Financi&egrave;re Africaine Francs"), _T("Benin, Burkina Faso, Mali, Niger, Senegal, Togo") },
        {_T("YER"), _T("Rials"), _T("Yemen") },
        {_T("ZAR"), _T("South Africa Rand"), _T("Lesotho") },
        {_T("ZMK"), _T("Kwacha"), _T("Zambia") },
        {_T("ZWD"), _T("Zimbabwe Dollars"), _T("Zimbabwe") }
    };

    uint_t getCurrenciesCount()
    {
        return CURRENCY_COUNT;
    }

    Currency getCurrency(int pos)
    {
        assert (pos<CURRENCY_COUNT);
        return Currency(currencies[pos].name, currencies[pos].abbrev, currencies[pos].countries);
        
    }
        // always return index value in (0, statesCount-1)   
    int getCurrencyIndexByFirstChar(ArsLexis::char_t inChar)
    {
        inChar = ArsLexis::toLower(inChar);
        // skip four first currencies USD, EUR, GBP and JPY
        // the rest is set alphabetically
        for (int i = 4; i < getCurrenciesCount(); i++)
        {
            char_t foundChar = ArsLexis::toLower(currencies[i].abbrev[0]);
            if (inChar <= foundChar)
                return i;
        }
        return getCurrenciesCount()-1;
    }    
}