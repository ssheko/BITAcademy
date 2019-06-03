using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

namespace MultiConverter
{
    [ValueConversion(typeof(string), typeof(string))]
    class Converter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            string firstName = (string)values[0];
            string lastName = (string)values[1];
            return firstName + " " + lastName;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        // convert의 반대. 값을 바꿔 DB에 업데이트할 경우에 사용.

    }
}
