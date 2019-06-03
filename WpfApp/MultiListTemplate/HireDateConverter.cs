using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

namespace MultiListTemplate
{
    [ValueConversion(typeof(DateTime), typeof(string))]
    class HireDateConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            //throw new NotImplementedException();
            DateTime date = (DateTime)value;
            return date.ToShortDateString();
        }

        // convert의 반대. 값을 바꿔 DB에 업데이트할 경우에 사용.
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            //throw new NotImplementedException();
            string strValue = value as string;
            DateTime resultDateTime;

            if (DateTime.TryParse(strValue, out resultDateTime))
            {
                return resultDateTime;
            }
            return DependencyProperty.UnsetValue;
        }
    }
}