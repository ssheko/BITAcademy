using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace MultiListTemplate
{
    [ValueConversion(typeof(string), typeof(string))]
    class Converter : IMultiValueConverter
    {

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            string retval = string.Format("{0} {1}", values[0], values[1]);
            return retval;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }


        // convert의 반대. 값을 바꿔 DB에 업데이트할 경우에 사용.

    }
}
