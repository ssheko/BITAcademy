using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConnectDB
{
    public partial class MainForm : Form
    {
        string[] columnName = { "EMPLOYEE_ID", "FIRST_NAME", "LAST_NAME", "EMAIL" ,
            "PHONE_NUMBER", "HIRE_DATE", "JOB_ID", "SALARY", "COMMISSION_PCT",
            "MANAGER_ID", "DEPARTMENT_ID"};
        public MainForm()
        {
            InitializeComponent();

            listAllEmployees.BeginUpdate();

            foreach(string str in columnName)
                listAllEmployees.Columns.Add(str);
            listAllEmployees.EndUpdate();
        }

        private void BtnView_Click(object sender, EventArgs e)
        {
            Employee employee = new Employee();

            employee = HrDAC.Instance.GetEmployee(long.Parse(txtBoxEmployeeID.Text));

            txtFirstName.Text =     employee.First_name;
            txtLastName.Text =      employee.Last_name;
            txtEmail.Text =         employee.Email;
            txtPhoneNumber.Text =   employee.Phone_number;
            txtHireDate.Text =      employee.Hire_date.ToShortDateString();
            txtJobID.Text =         employee.Job_id;
            txtSalary.Text =        employee.Salary.ToString();
            txtCommisionPCT.Text =  employee.Commission_pct.ToString();
            txtManagerID.Text =     employee.Employee_id.ToString();
            txtDepartmentID.Text =  employee.Department_id.ToString();
        }

        private void BtnSearchAll_Click(object sender, EventArgs e)
        {
            List<Employee> employees = new List<Employee>();
            employees = HrDAC.Instance.GetEmployee();

            foreach (Employee employee in employees)
            {
                ListViewItem listViewItem = new ListViewItem(employee.Employee_id.ToString());
                listViewItem.SubItems.Add(employee.First_name);
                listViewItem.SubItems.Add(employee.Last_name);
                listViewItem.SubItems.Add(employee.Email);
                listViewItem.SubItems.Add(employee.Phone_number);
                listViewItem.SubItems.Add(employee.Hire_date.ToShortDateString());
                listViewItem.SubItems.Add(employee.Job_id);
                listViewItem.SubItems.Add(employee.Salary.ToString());
                listViewItem.SubItems.Add(employee.Commission_pct.ToString());
                listViewItem.SubItems.Add(employee.Manager_id.ToString());
                listViewItem.SubItems.Add(employee.Department_id.ToString());

                listAllEmployees.Items.Add(listViewItem);
            }

            listAllEmployees.EndUpdate();
        }
    }
}
